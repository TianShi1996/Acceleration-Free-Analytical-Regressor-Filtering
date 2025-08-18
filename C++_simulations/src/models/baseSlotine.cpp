#include <filtered_regressor/franka_model.h>

using namespace std;
Eigen::Matrix7_64 Base_Slotine_Panda(const Eigen::Vector7_1& q,
                                     const Eigen::Vector7_1& q_dot,
                                     const Eigen::Vector7_1& qr_dot,
                                     const Eigen::Vector7_1& qr_ddot) {
  Eigen::Matrix7_64 slotine;
  Eigen::Vector7_1 zero = Eigen::Matrix<double, 7, 1>::Zero();  //之前没初始化...
//   Eigen::Matrix7_64 Y_qr_q_dot = Base_Regressor_Panda(q, q_dot + qr_dot, qr_ddot);
//   Eigen::Matrix7_64 Y_qr_dot = Base_Regressor_Panda(q, qr_dot, qr_ddot);
//   Eigen::Matrix7_64 Y_q_dot = Base_Regressor_Panda(q, q_dot, qr_ddot);
//   Eigen::Matrix7_64 Y_0 = Base_Regressor_Panda(q, zero, qr_ddot);
//   slotine = 0.5 * (Y_qr_q_dot - Y_qr_dot - Y_q_dot + 3 * Y_0);


Eigen::Matrix7_64 Y_qr_q_dot = base_regressor_without_fiction(q, q_dot + qr_dot, qr_ddot);
  Eigen::Matrix7_64 Y_qr_dot = base_regressor_without_fiction(q, qr_dot, qr_ddot);
  Eigen::Matrix7_64 Y_q_dot = base_regressor_without_fiction(q, q_dot, qr_ddot);
  Eigen::Matrix7_64 Y_0 = base_regressor_without_fiction(q, zero, qr_ddot);
  slotine = 0.5 * (Y_qr_q_dot - Y_qr_dot - Y_q_dot + 3 * Y_0);
 
    slotine(0, 1) = 0;
  slotine(0, 2) = 0;
  slotine(0, 3) = 0;
  slotine(1, 11) = 0;
  slotine(1, 12) = 0;
  slotine(1, 13) = 0;
  slotine(2, 21) = 0;
  slotine(2, 22) = 0;
  slotine(2, 23) = 0;
  slotine(3, 31) = 0;
  slotine(3, 32) = 0;
  slotine(3, 33) = 0;
  slotine(4, 41) = 0;
  slotine(4, 42) = 0;
  slotine(4, 43) = 0;
  slotine(5, 51) = 0;
  slotine(5, 52) = 0;
  slotine(5, 53) = 0;
  slotine(6, 61) = 0;
  slotine(6, 62) = 0;
  slotine(6, 63) = 0;
  

//   slotine(0, 1) = Y_q_dot(0, 1);
//   slotine(0, 2) = Y_q_dot(0, 2);
//   slotine(0, 3) = Y_q_dot(0, 3);
//   slotine(1, 11) = Y_q_dot(1, 11);
//   slotine(1, 12) = Y_q_dot(1, 12);
//   slotine(1, 13) = Y_q_dot(1, 13);
//   slotine(2, 21) = Y_q_dot(2, 21);
//   slotine(2, 22) = Y_q_dot(2, 22);
//   slotine(2, 23) = Y_q_dot(2, 23);
//   slotine(3, 31) = Y_q_dot(3, 31);
//   slotine(3, 32) = Y_q_dot(3, 32);
//   slotine(3, 33) = Y_q_dot(3, 33);
//   slotine(4, 41) = Y_q_dot(4, 41);
//   slotine(4, 42) = Y_q_dot(4, 42);
//   slotine(4, 43) = Y_q_dot(4, 43);
//   slotine(5, 51) = Y_q_dot(5, 51);
//   slotine(5, 52) = Y_q_dot(5, 52);
//   slotine(5, 53) = Y_q_dot(5, 53);
//   slotine(6, 61) = Y_q_dot(6, 61);
//   slotine(6, 62) = Y_q_dot(6, 62);
//   slotine(6, 63) = Y_q_dot(6, 63);

  return slotine;
}

Eigen::Matrix7_64 Base_Slotine_Panda_noG(const Eigen::Vector7_1& q,
                                         const Eigen::Vector7_1& q_dot,
                                         const Eigen::Vector7_1& qr_dot,
                                         const Eigen::Vector7_1& qr_ddot) {
  Eigen::Matrix7_64 slotine;
  Eigen::Vector7_1 zero = Eigen::Matrix<double, 7, 1>::Zero();  //之前没初始化...
  Eigen::Matrix7_64 Y_qr_q_dot = Base_Regressor_Panda_noG(q, q_dot + qr_dot, qr_ddot);
  Eigen::Matrix7_64 Y_qr_dot = Base_Regressor_Panda_noG(q, qr_dot, qr_ddot);
  Eigen::Matrix7_64 Y_q_dot = Base_Regressor_Panda_noG(q, q_dot, qr_ddot);
  Eigen::Matrix7_64 Y_0 = Base_Regressor_Panda_noG(q, zero, qr_ddot);
  slotine = 0.5 * (Y_qr_q_dot - Y_qr_dot - Y_q_dot + 3 * Y_0);

  slotine(0, 1) = Y_q_dot(0, 1);
  slotine(0, 2) = Y_q_dot(0, 2);
  slotine(0, 3) = 0;  // Y_q_dot(0,3);
  slotine(1, 11) = Y_q_dot(1, 11);
  slotine(1, 12) = Y_q_dot(1, 12);
  slotine(1, 13) = 0;  // Y_q_dot(1,13);
  slotine(2, 21) = Y_q_dot(2, 21);
  slotine(2, 22) = Y_q_dot(2, 22);
  slotine(2, 23) = 0;  // Y_q_dot(2,23);
  slotine(3, 31) = Y_q_dot(3, 31);
  slotine(3, 32) = Y_q_dot(3, 32);
  slotine(3, 33) = 0;  // Y_q_dot(3,33);
  slotine(4, 41) = Y_q_dot(4, 41);
  slotine(4, 42) = Y_q_dot(4, 42);
  slotine(4, 43) = 0;  // Y_q_dot(4,43);
  slotine(5, 51) = Y_q_dot(5, 51);
  slotine(5, 52) = Y_q_dot(5, 52);
  slotine(5, 53) = 0;  // Y_q_dot(5,53);
  slotine(6, 61) = Y_q_dot(6, 61);
  slotine(6, 62) = Y_q_dot(6, 62);
  slotine(6, 63) = 0;  // Y_q_dot(6,63);

  return slotine;
}
