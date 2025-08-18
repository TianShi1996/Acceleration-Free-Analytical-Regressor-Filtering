#ifndef __PHI_FILTER_H__
#define __PHI_FILTER_H__

#include "franka_model.h"
extern Eigen::Matrix7_64 Base_Regressor_Fiction_Panda(const Eigen::Vector7_1 &dq);
extern Eigen::Matrix7_64 Base_Regressor_Panda(const Eigen::Vector7_1 &q, const Eigen::Vector7_1 &dq,
                                              const Eigen::Vector7_1 &ddq);
Eigen::Matrix7_64 Base_Regressor_Panda_NoF(const Eigen::Vector7_1 &q, const Eigen::Vector7_1 &dq,
                                           const Eigen::Vector7_1 &ddq);
Eigen::Matrix<double, 7, 64> filtered_regressor(const Eigen::Matrix<double, 7, 1> &q,
                                                const Eigen::Matrix<double, 7, 1> &q_dot, const double filter_param,
                                                const double sample_time);
Eigen::Matrix<double, 7, 64> base_regressor_without_fiction(const Eigen::Matrix<double, 7, 1> &q,
                                                            const Eigen::Matrix<double, 7, 1> &q_dot,
                                                            const Eigen::Matrix<double, 7, 1> &q_ddot);

Eigen::Matrix<double, 7, 64> base_regressor_fiction(const Eigen::Matrix<double, 7, 1> &q_dot);

Eigen::Matrix7_64 regressor_matrix_filter(const Eigen::Vector7_1 q, const Eigen::Vector7_1 &v, double m_cof,
                                          double filter_cof, double sample_time);

#endif
