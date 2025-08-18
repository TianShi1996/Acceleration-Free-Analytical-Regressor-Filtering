//
// Created by robot on 3/27/24.
//

#ifndef REAL_PARAMETER_H
#define REAL_PARAMETER_H

#include "franka_model.h"
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigen>

struct real_parameters
{
    // 回归矩阵43*1
    Eigen::Vector43_1 params43;
    Eigen::Vector43_1 params43_real;
    Eigen::Matrix7_43 slotine43;
    Eigen::Vector43_1 params43_dot;
    Eigen::Matrix43_43 gamma43;

    // 回归矩阵64*1
    Eigen::Vector64_1 base_params_real;
    Eigen::Vector64_1 base_params;

    Eigen::Vector64_1 base_params_withoutfriction_real;

    Eigen::Vector64_1 base_params_NoF;
    Eigen::Matrix7_64 base_slotine;
    Eigen::Vector64_1 base_params_dot;
    Eigen::Matrix64_64 base_gamma1;
    Eigen::Matrix64_64 base_gamma2;

    // 回归矩阵91*1
    Eigen::Vector91_1 all_params_real;
    Eigen::Vector91_1 all_params_real_NoF;
    Eigen::Matrix7_91 all_slotine;
    Eigen::Vector91_1 all_params_dot;
    Eigen::Matrix91_91 all_gamma;

    // 70*1
    Eigen::Matrix<double, 70, 1> full_params_real;

    real_parameters();
};


#endif  // MCG_TAU_TRACKING_VISP_ROS_REAL_PARAMETER_H
