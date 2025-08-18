#ifndef SIM_REGRESSOR_H
#define SIM_REGRESSOR_H
#include <Eigen/Dense>

#include <pinocchio/algorithm/aba.hpp>
#include <pinocchio/algorithm/centroidal.hpp>
#include <pinocchio/algorithm/compute-all-terms.hpp>
#include <pinocchio/algorithm/crba.hpp>
#include <pinocchio/algorithm/dynamics.hpp>
#include <pinocchio/algorithm/frames.hpp>
#include <pinocchio/algorithm/joint-configuration.hpp>
#include <pinocchio/algorithm/kinematics.hpp>
#include <pinocchio/algorithm/model.hpp>
#include <pinocchio/algorithm/regressor.hpp>
#include <pinocchio/algorithm/rnea-derivatives.hpp>
#include <pinocchio/algorithm/rnea.hpp>
#include <pinocchio/parsers/urdf.hpp>


#include <algorithm>
#include <iostream>
#include <vector>

#include "ros/init.h"
#include "ros/node_handle.h"
#include "ros/publisher.h"
#include "std_msgs/Float64.h"
#include <filtered_regressor/PhiFilter.h>
#include <filtered_regressor/franka_model.h>
#include <filtered_regressor/real_parameter.h>

#define ROBOT_DOF 7

void pub_double(ros::Publisher &pub, double value);
template <typename VectorType>
void pub_double7(ros::Publisher &pub, const VectorType &value);
Eigen::Matrix7_43 Base_Slotine_Panda_nof(const Eigen::Vector7_1 &q, const Eigen::Vector7_1 &q_dot,
                                         const Eigen::Vector7_1 &qr_dot, const Eigen::Vector7_1 &qr_ddot);
Eigen::Matrix7_64 Base_Slotine_Panda_pino(const Eigen::Vector7_1 &q, const Eigen::Vector7_1 &q_dot,
                                          const Eigen::Vector7_1 &qr_dot, const Eigen::Vector7_1 &qr_ddot);
Eigen::Matrix<double, 7, 64> filtered_regressor_pino(const Eigen::Matrix<double, 7, 1> &q,
                                                     const Eigen::Matrix<double, 7, 1> &q_dot, const double kLambda,
                                                     const double sample_time);

#endif  // SIM_REGRESSOR_H