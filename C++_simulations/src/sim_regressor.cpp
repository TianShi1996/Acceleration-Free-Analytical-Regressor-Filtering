#include <filtered_regressor/sim_regressor.h>

int main(int argc, char **argv)
{
    // Load the URDF model
    pinocchio::Model model;
    pinocchio::urdf::buildModel(BASE_PWD "/data/panda.urdf", model);
    Eigen::MatrixXd Y;

    // Create data structure for kinematics
    pinocchio::Data data(model);

    std::vector<Eigen::Vector7_1> desired_q_vec, dqd_vec, ddqd_vec;
    auto idx_desired_q = desired_q_vec.begin(), idx_dqd = dqd_vec.begin(), idx_ddqd = ddqd_vec.begin();
    Eigen::Vector7_1 qJoint, dqJoint, ddqJoint, tau, dot_qrFilted;
    qJoint = dqJoint = ddqJoint = Eigen::Vector7_1::Zero();
    // Eigen::Vector7_1 dq_K1(ROBOT_DOF, 0), dq_K2(ROBOT_DOF, 0), dq_K3(ROBOT_DOF,
    // 0), dq_K4(ROBOT_DOF, 0); Eigen::Vector7_1 ddq_L1(ROBOT_DOF, 0),
    // ddq_L2(ROBOT_DOF, 0), ddq_L3(ROBOT_DOF, 0), ddq_L4(ROBOT_DOF, 0);
    Eigen::Vector64_1 W_hat, dot_W_hat;
    Eigen::Vector64_1 dW_K1, dW_K2, dW_K3, dW_K4;
    Eigen::Vector7_1 tau_filtered = Eigen::Vector7_1::Zero();
    Eigen::MatrixXd tt, tt1;
    Eigen::Matrix64_64 filter_ExtenRegressor = Eigen::Matrix64_64::Zero();
    Eigen::Vector64_1 filter_params = Eigen::Vector64_1::Zero();
    Eigen::Matrix<double, 7, 7> I = Eigen::Matrix<double, 7, 7>::Identity();
    Eigen::Matrix<double, 7, 7> MassMatrix = Eigen::Matrix<double, 7, 7>::Zero();

    Eigen::Matrix7_64 Phi, Phif;
    dot_W_hat = W_hat = Eigen::Matrix<double, 64, 1>::Zero();  // 初始化参数向量
    const double kLambda = 15;
    double dt = 2e-4;
    double t = 0, stop_time = 100;
    ros::init(argc, argv, "test_pino");
    ros::NodeHandle nh;
    auto pub_e_norm = nh.advertise<std_msgs::Float64>("e_norm", 1);
    auto pub_W_norm = nh.advertise<std_msgs::Float64>("W_norm", 1);
    auto pub_tau_norm = nh.advertise<std_msgs::Float64>("tau_norm", 1);
    auto pub_est_err_norm = nh.advertise<std_msgs::Float64>("est_err_norm", 1);
    std_msgs::Float64 msg;
    std::vector<double> est_err_vec, time_reg_vec, eps_vec;
    std::vector<Eigen::Vector7_1> e_vec;

    int use_analytic = 0;
    nh.param<int>("use_analytic", use_analytic, 0);  // 0: use pinocchio, 1: use analytic

    std::cout << "use_analytic param: " << use_analytic << std::endl;

    std::ifstream infile(BASE_PWD "/data/traj/q_traj.csv");
    std::string line;
    while (std::getline(infile, line))
    {
        std::stringstream ss(line);
        Eigen::Vector7_1 qd = Eigen::Vector7_1::Zero();
        for (int i = 0; i < ROBOT_DOF; ++i)
        {
            std::string value;
            if (!std::getline(ss, value, ',')) break;
            qd[i] = std::stod(value);
        }
        desired_q_vec.push_back(qd);
    }
    idx_desired_q = desired_q_vec.begin();
    std::ifstream infile_dqd(BASE_PWD "/data/traj/dq_traj.csv");
    if (!infile_dqd.is_open())
    {
        std::cerr << "Error: Unable to open file " << BASE_PWD "/data/traj/dq_traj.csv" << std::endl;
    }
    while (std::getline(infile_dqd, line))
    {
        std::stringstream ss(line);
        Eigen::Vector7_1 dqd = Eigen::Vector7_1::Zero();
        for (int i = 0; i < ROBOT_DOF; ++i)
        {
            std::string value;
            if (!std::getline(ss, value, ',')) break;
            dqd[i] = std::stod(value);
        }
        dqd_vec.push_back(dqd);
    }
    idx_dqd = dqd_vec.begin();

    std::ifstream infile_ddqd(BASE_PWD "/data/traj/ddq_traj.csv");
    while (std::getline(infile_ddqd, line))
    {
        std::stringstream ss(line);
        Eigen::Vector7_1 ddqd = Eigen::Vector7_1::Zero();
        for (int i = 0; i < ROBOT_DOF; ++i)
        {
            std::string value;
            if (!std::getline(ss, value, ',')) break;
            ddqd[i] = std::stod(value);
        }
        ddqd_vec.push_back(ddqd);
    }
    idx_ddqd = ddqd_vec.begin();

    qJoint = *idx_desired_q;
    dqJoint = *idx_dqd;

    const real_parameters real_para;
    std::cout << "\033[2J\033[H";

    // Simulation Loop
    for (t = 0; t < stop_time; t += dt)
    {
        if (static_cast<int>(t / dt) % static_cast<int>(10.0) == 0) { std::cout << "\033[2J\033[H"; }
        auto reg_start = std::chrono::high_resolution_clock::now();

        std::cout << "\033[H";
        auto desired_q = *idx_desired_q++;
        auto dqd = *idx_dqd++;
        auto ddqd = *idx_ddqd++;
        std::cout << "\n\ndesired_q: " << desired_q.transpose() << std::endl;
        std::cout << "dqd: " << dqd.transpose() << std::endl;
        std::cout << "ddqd: " << ddqd.transpose() << std::endl;
        Eigen::Vector7_1 e = desired_q - qJoint;
        e_vec.push_back(e);
        auto dot_qr = dqd + 10 * e;
        auto de = dqd - dqJoint;
        auto ddot_qr = ddqd + 10 * de;
        auto ef = dot_qr - dqJoint;
        std::cout << "e: " << e.transpose() << "\ne.norm(): " << e.norm() << std::endl;
        pub_double(pub_e_norm, e.norm());

        tau_filtered = tau_filtered + dt * kLambda * (tau - tau_filtered);

        if (use_analytic)
        {
            Phi = Base_Slotine_Panda(qJoint, (dqJoint), (dot_qr), (ddot_qr));

            auto reg_start = std::chrono::high_resolution_clock::now();
            Phif = filtered_regressor(qJoint, dqJoint, kLambda, dt);
            auto reg_end = std::chrono::high_resolution_clock::now();
            auto reg_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(reg_end - reg_start).count();

            time_reg_vec.push_back(static_cast<double>(reg_duration));
        } else
        {
            Phi = Base_Slotine_Panda_pino(qJoint, dqJoint, dot_qr, ddot_qr);

            auto reg_start = std::chrono::high_resolution_clock::now();
            Phif = filtered_regressor_pino(qJoint, dqJoint, kLambda, dt);
            auto reg_end = std::chrono::high_resolution_clock::now();
            auto reg_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(reg_end - reg_start).count();
            time_reg_vec.push_back(static_cast<double>(reg_duration));
        }

        auto ExtenRegressor = Phif.transpose() * Phif;
        auto ExtenY = Phif.transpose() * tau_filtered;
        eps_vec.push_back((tau_filtered - Phif * W_hat).norm());
        if (t < 25.0 && t >= dt)
        {
            filter_params = filter_params + dt * ExtenY;
            filter_ExtenRegressor = filter_ExtenRegressor + dt * ExtenRegressor;
        }
        dot_W_hat = 0.4 * Phi.transpose() * ef + 0.4 * (filter_params - filter_ExtenRegressor * W_hat);
        W_hat += 1 * dot_W_hat * dt;  // 更新参数向量
        est_err_vec.push_back((W_hat - real_para.base_params_withoutfriction_real).norm());

        // ODE4
        // dW_K1=0.4 * Phi.transpose() * vispToEigen7(ef) + 0.4 * (filter_params -
        // filter_ExtenRegressor * W_hat); dW_K2=0.4 * Phi.transpose() *
        // vispToEigen7(ef) + 0.4 * (filter_params - filter_ExtenRegressor *
        // W_hat+dt/2*dW_K1); dW_K3=0.4 * Phi.transpose() * vispToEigen7(ef) + 0.4 *
        // (filter_params - filter_ExtenRegressor * W_hat+dt/2*dW_K2); dW_K2=0.4 *
        // Phi.transpose() * vispToEigen7(ef) + 0.4 * (filter_params -
        // filter_ExtenRegressor * W_hat+dt*dW_K3);

        // W_hat += dt/6*(dW_K1 + 2*dW_K2 + 2*dW_K3 + dW_K4);

        std::cout << "t: " << t << ", W_hat: " << W_hat.norm() << ", dot_w_hat: " << dot_W_hat.norm() << std::endl;
        pub_double(pub_W_norm, W_hat.norm());
        if (W_hat.norm() > 8) return -1;
        Eigen::Matrix<double, 7, 7> dampGainJoint;
        dampGainJoint.diagonal() = (Eigen::Matrix<double, 7, 1>() << 20, 20, 20, 20, 8, 8, 5).finished();
        auto tau_damp = dampGainJoint * ef;

        tau = Phi * W_hat + tau_damp;

        auto reg_end = std::chrono::high_resolution_clock::now();
        auto reg_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(reg_end - reg_start).count();

        time_reg_vec.push_back(static_cast<double>(reg_duration));

        std::cout << "tau: " << tau.transpose() << std::endl;
        pub_double(pub_tau_norm, tau.norm());
        std::cout << "W_hat norm: " << W_hat.norm() << std::endl;
        std::cout << "params_err: " << (W_hat - real_para.base_params_withoutfriction_real).norm() << std::endl;
        pub_double(pub_est_err_norm, (W_hat - real_para.base_params_withoutfriction_real).norm());

        for (int ii = 0; ii < 7; ii++)
        {
            MassMatrix.col(ii) =
                (base_regressor_without_fiction((qJoint), Eigen::Vector7_1::Zero(), I.col(ii))
                 - base_regressor_without_fiction((qJoint), Eigen::Vector7_1::Zero(), Eigen::Vector7_1::Zero()))
                * real_para.base_params_withoutfriction_real;
        }

        ddqJoint = MassMatrix.inverse()
                   * (tau
                      - ((base_regressor_without_fiction(qJoint, dqJoint, Eigen::Vector7_1::Zero()))
                         * real_para.base_params_withoutfriction_real));

        dqJoint += ddqJoint * dt;
        qJoint += dqJoint * dt;
        // qJoint += dqJoint * dt + 0.5 * ddqJoint * dt * dt;

        // Runge-Kutta ODE
        // dq_K1=dqJoint;
        // ddq_L1=vpMassMatrix.inverseByQR()
        //     * (tau
        //        - EigenToVisp(
        //            ((Base_Regressor_Panda(vispToEigen7(qJoint),
        //            vispToEigen7(dqJoint), vispToEigen7(vpColVector(7, 0))))
        //             * real_para.base_params_withoutfriction_real)));
        // M_Panda_new(vpMassMatrix, real_para.full_params_real, qJoint+dt/2*dq_K1);
        // dq_K2=dqJoint+dt/2*ddq_L1;
        // ddq_L2=vpMassMatrix.inverseByQR()
        //     * (tau
        //        - EigenToVisp(
        //            ((Base_Regressor_Panda(vispToEigen7(qJoint+dt/2*dq_K1),
        //            vispToEigen7(dqJoint+dt/2*ddq_L1), vispToEigen7(vpColVector(7,
        //            0))))
        //             * real_para.base_params_withoutfriction_real)));
        // M_Panda_new(vpMassMatrix, real_para.full_params_real, qJoint+dt/2*dq_K2);
        // dq_K3=dqJoint+dt/2*ddq_L2;
        // ddq_L3=vpMassMatrix.inverseByQR()
        //     * (tau
        //        - EigenToVisp(
        //            ((Base_Regressor_Panda(vispToEigen7(qJoint+dt/2*dq_K2),
        //            vispToEigen7(dqJoint+dt/2*ddq_L2), vispToEigen7(vpColVector(7,
        //            0))))
        //             * real_para.base_params_withoutfriction_real)));
        // M_Panda_new(vpMassMatrix, real_para.full_params_real, qJoint+dt*dq_K3);
        // dq_K4=dqJoint+dt*ddq_L3;
        // ddq_L4=vpMassMatrix.inverseByQR()
        //     * (tau
        //        - EigenToVisp(
        //            ((Base_Regressor_Panda(vispToEigen7(qJoint+dt*dq_K3),
        //            vispToEigen7(dqJoint+dt*ddq_L3), vispToEigen7(vpColVector(7,
        //            0))))
        //             * real_para.base_params_withoutfriction_real)));
        // dqJoint += dt/6*(ddq_L1+2*ddq_L2+2*ddq_L3+ddq_L4);
        // qJoint += dt/6*(dq_K1+2*dq_K2+2*dq_K3+dq_K4);

        std::cout << std::flush;
    }
    std::cout << "\n\n\n";
    std::ofstream outfile(BASE_PWD "/data/record/estimation_results.csv");
    if (outfile.is_open())
    {
        // Write header
        outfile << "est_err,time_reg,eps,para_err\n";
        size_t max_size = std::max({est_err_vec.size(), time_reg_vec.size(), eps_vec.size()});
        for (size_t i = 0; i < max_size; ++i)
        {
            if (i < est_err_vec.size())
                outfile << est_err_vec[i];
            else
                outfile << "";
            outfile << ",";
            if (i < time_reg_vec.size())
                outfile << time_reg_vec[i];
            else
                outfile << "";
            outfile << ",";
            if (i < eps_vec.size())
                outfile << eps_vec[i];
            else
                outfile << "";
            outfile << "\n";
        }
        outfile.close();
        std::cout << "Saved estimation results to estimation_results.csv" << std::endl;
    } else
    {
        std::cerr << "Error: Unable to open estimation_results.csv for writing." << std::endl;
    }
    std::ofstream efile(BASE_PWD "/data/record/e_vec.csv");
    if (efile.is_open())
    {
        // 写表头
        for (int i = 0; i < ROBOT_DOF; ++i)
        {
            efile << "e" << i;
            if (i < ROBOT_DOF - 1) efile << ",";
        }
        efile << "\n";
        for (const auto &e : e_vec)
        {
            for (int i = 0; i < ROBOT_DOF; ++i)
            {
                efile << e[i];
                if (i < ROBOT_DOF - 1) efile << ",";
            }
            efile << "\n";
        }
        efile.close();
        std::cout << "Saved e_vec to e_vec.csv" << std::endl;
    } else
    {
        std::cerr << "Error: Unable to open e_vec.csv for writing." << std::endl;
    }

    return 0;
}

Eigen::Matrix<double, 7, 64> compute_base_regressor_nof(const Eigen::Matrix<double, 7, 1> &q_in,
                                                        const Eigen::Matrix<double, 7, 1> &v_in,
                                                        const Eigen::Matrix<double, 7, 1> &a_in)
{
    static pinocchio::Model model;
    static Eigen::MatrixXd P;
    // initialize
    if (P.rows() == 0)
    {
        pinocchio::urdf::buildModel(BASE_PWD "/data/panda.urdf", model);
        P.resize(70, 64);
        P.setZero();
        std::vector<int> empty_P_idx = {1,  2,  3,  11, 12, 13, 21, 22, 23, 31, 32,
                                        33, 41, 42, 43, 51, 52, 53, 61, 62, 63};
        // 读取文件
        std::ifstream file(BASE_PWD "/data/P.csv");
        if (!file.is_open())
        {
            std::cerr << "Error opening P.csv file." << std::endl;
        } else
        {
            std::string line;
            int row = 0;
            while (std::getline(file, line))
            {
                // std::cout << "row: " <<row  << " line: " << line << std::endl;
                std::stringstream ss(line);
                for (int col = 0; col < 64; ++col)
                {
                    if (!(ss >> P(row, col))) { std::cerr << "Error reading value from P.csv." << std::endl; }
                    if (ss.peek() == ',') ss.ignore();
                }
                ++row;
            }
            file.close();
        }
    }
    pinocchio::Data data(model);
    pinocchio::computeJointTorqueRegressor(model, data, q_in, v_in, a_in);
    auto Y = data.jointTorqueRegressor;  // 7x70
    // std::cout << "compute  compute_base_regressor_nof finish\n";
    return Y * P;
};

Eigen::Matrix7_64 Base_Slotine_Panda_pino(const Eigen::Vector7_1 &q, const Eigen::Vector7_1 &q_dot,
                                          const Eigen::Vector7_1 &qr_dot, const Eigen::Vector7_1 &qr_ddot)
{
    Eigen::Matrix7_64 slotine;
    Eigen::Vector7_1 zero = Eigen::Matrix<double, 7, 1>::Zero();  //之前没初始化...
    Eigen::Matrix7_64 Y_qr_q_dot = compute_base_regressor_nof(q, q_dot + qr_dot, qr_ddot);
    Eigen::Matrix7_64 Y_qr_dot = compute_base_regressor_nof(q, qr_dot, qr_ddot);
    Eigen::Matrix7_64 Y_q_dot = compute_base_regressor_nof(q, q_dot, qr_ddot);
    Eigen::Matrix7_64 Y_0 = compute_base_regressor_nof(q, zero, qr_ddot);
    slotine = 0.5 * (Y_qr_q_dot - Y_qr_dot - Y_q_dot + 3 * Y_0);

    slotine(0, 1) = Y_q_dot(0, 1);
    slotine(0, 2) = Y_q_dot(0, 2);
    slotine(0, 3) = Y_q_dot(0, 3);
    slotine(1, 11) = Y_q_dot(1, 11);
    slotine(1, 12) = Y_q_dot(1, 12);
    slotine(1, 13) = Y_q_dot(1, 13);
    slotine(2, 21) = Y_q_dot(2, 21);
    slotine(2, 22) = Y_q_dot(2, 22);
    slotine(2, 23) = Y_q_dot(2, 23);
    slotine(3, 31) = Y_q_dot(3, 31);
    slotine(3, 32) = Y_q_dot(3, 32);
    slotine(3, 33) = Y_q_dot(3, 33);
    slotine(4, 41) = Y_q_dot(4, 41);
    slotine(4, 42) = Y_q_dot(4, 42);
    slotine(4, 43) = Y_q_dot(4, 43);
    slotine(5, 51) = Y_q_dot(5, 51);
    slotine(5, 52) = Y_q_dot(5, 52);
    slotine(5, 53) = Y_q_dot(5, 53);
    slotine(6, 61) = Y_q_dot(6, 61);
    slotine(6, 62) = Y_q_dot(6, 62);
    slotine(6, 63) = Y_q_dot(6, 63);

    return slotine;
}

Eigen::Matrix<double, 7, 64> filtered_regressor_pino(const Eigen::Matrix<double, 7, 1> &q,
                                                     const Eigen::Matrix<double, 7, 1> &q_dot,
                                                     const double filter_param, const double sample_time)
{
    Eigen::Matrix<double, 7, 1> zero = Eigen::Matrix<double, 7, 1>::Zero();
    Eigen::Matrix<double, 7, 7> I = Eigen::Matrix<double, 7, 7>::Identity();
    Eigen::Matrix<double, 7, 64> C_q_q_dot_q_dot = Eigen::Matrix<double, 7, 64>::Zero();
    Eigen::Matrix<double, 7, 64> regressor_c = Eigen::Matrix<double, 7, 64>::Zero();
    Eigen::Matrix<double, 1, 64> row_c = Eigen::Matrix<double, 1, 64>::Zero();
    static Eigen::Matrix<double, 7, 64> filter_regressor = Eigen::Matrix<double, 7, 64>::Zero();
    Eigen::Matrix<double, 7, 64> g = compute_base_regressor_nof(q, zero, zero);
    Eigen::Matrix<double, 7, 64> M_q_q_dot = compute_base_regressor_nof(q, zero, q_dot) - g;
    Eigen::Matrix<double, 7, 64> fiction = base_regressor_fiction(q_dot);

    for (int i = 0; i < 7; i++)
    {
        regressor_c = 0.5
                      * (compute_base_regressor_nof(q, q_dot + I.col(i), zero) + g
                         - compute_base_regressor_nof(q, q_dot, zero) - compute_base_regressor_nof(q, I.col(i), zero));
        row_c = q_dot.transpose() * regressor_c;
        C_q_q_dot_q_dot.row(i) = row_c;
    }

    filter_regressor = filter_regressor
                       + filter_param * sample_time
                             * ((-filter_param * M_q_q_dot + g - C_q_q_dot_q_dot) - filter_regressor);  //+ fiction

    return filter_regressor + filter_param * M_q_q_dot;
};

void pub_double(ros::Publisher &pub, double value)
{
    std_msgs::Float64 msg;
    msg.data = value;
    pub.publish(msg);
}
