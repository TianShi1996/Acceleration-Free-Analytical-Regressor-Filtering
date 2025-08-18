/*
 * franka_model.h
 *
 *  Created on: 24 feb 2019
 *     Authors: Oliva Alexander, Gaz Claudio, Cognetti Marco
 *
 *  C. Gaz, M. Cognetti, A. Oliva, P. Robuffo Giordano, A. De Luca, 'Dynamic
 *  Identification of the Franka Emika Panda Robot With Retrieval of Feasible
 *  Parameters Using Penalty-Based Optimization'. IEEE RA-L, 2019.
 *
 */


#include <eigen3/Eigen/Core>

#include <eigen3/Eigen/Dense>

#ifndef INCLUDE_FRANKA_MODEL_H_
#define INCLUDE_FRANKA_MODEL_H_

#define NUMBER_OF_JOINTS 7

namespace Eigen {

	typedef Eigen::Matrix< double , NUMBER_OF_JOINTS , NUMBER_OF_JOINTS > Matrix7_7;
	typedef Eigen::Matrix< double , NUMBER_OF_JOINTS , 1 > Vector7_1;
    

    typedef Eigen::Matrix< double , 43 , 1 > Vector43_1;
    typedef Eigen::Matrix< double , 64 , 1 > Vector64_1;
    typedef Eigen::Matrix< double , 84 , 1 > Vector84_1;
    typedef Eigen::Matrix< double , 91 , 1 > Vector91_1;

    typedef Eigen::Matrix< double , 7 , 43 > Matrix7_43;   
    typedef Eigen::Matrix< double , 7 , 64 > Matrix7_64;    
    typedef Eigen::Matrix< double , 7 , 84 > Matrix7_84;
    typedef Eigen::Matrix< double , 7 , 91 > Matrix7_91;

    typedef Eigen::Matrix< double , 43 , 43 > Matrix43_43;
    typedef Eigen::Matrix< double , 64 , 64 > Matrix64_64;
    typedef Eigen::Matrix< double , 84 , 84 > Matrix84_84;
    typedef Eigen::Matrix< double , 91 , 91 > Matrix91_91;


	// typedef Eigen::Matrix< double , NUMBER_OF_JOINTS , 1 > Vector7_1;
    // typedef Eigen::Matrix< double , 84 , 1 > Vector84_1;
    // typedef Eigen::Matrix< double , 7 , 84 > Matrix7_84;
    // typedef Eigen::Matrix< double , 84 , 84 > Matrix84d;
}

// s 7*1  params 84*1  tau 7*1   Y 7*84 
using namespace std;

/*
 * In order to speed up the code execution, we pre-compute the constant part of the
 * friction model of each joint i (second term of the right member of the equation).
 *
 * tau_f(i) = FI_1(i)/(1+exp(-FI_2(i)*(dq(i)+FI_3(i)))) -FI_1(i)/(1+exp(-FI_2(i)*FI_3(i)))
 *
 * For further information refer to our paper and relative Supplementary Material:
 *      C. Gaz, M. Cognetti, A. Oliva, P. Robuffo Giordano, A. De Luca,
 * 'Dynamic Identification of the Franka Emika Panda Robot With Retrieval of
 *   Feasible Parameters Using Penalty-Based Optimization'. IEEE RA-L, 2019.
 */

// const double  FI_11 = 0.54615;
// const double  FI_12 = 0.87224;
// const double  FI_13 = 0.64068;
// const double  FI_14 = 1.2794;
// const double  FI_15 = 0.83904;
// const double  FI_16 = 0.30301;
// const double  FI_17 = 0.56489;

// const double  FI_21 = 5.1181;
// const double  FI_22 = 9.0657;
// const double  FI_23 = 10.136;
// const double  FI_24 = 5.5903;
// const double  FI_25 = 8.3469;
// const double  FI_26 = 17.133;
// const double  FI_27 = 10.336;

// const double  FI_31 = 0.039533;
// const double  FI_32 = 0.025882;
// const double  FI_33 = -0.04607;
// const double  FI_34 = 0.036194;
// const double  FI_35 = 0.026226;
// const double  FI_36 = -0.021047;
// const double  FI_37 = 0.0035526;

// const double TAU_F_CONST_1 = FI_11/(1+exp(-FI_21*FI_31));
// const double TAU_F_CONST_2 = FI_12/(1+exp(-FI_22*FI_32));
// const double TAU_F_CONST_3 = FI_13/(1+exp(-FI_23*FI_33));
// const double TAU_F_CONST_4 = FI_14/(1+exp(-FI_24*FI_34));
// const double TAU_F_CONST_5 = FI_15/(1+exp(-FI_25*FI_35));
// const double TAU_F_CONST_6 = FI_16/(1+exp(-FI_26*FI_36));
// const double TAU_F_CONST_7 = FI_17/(1+exp(-FI_27*FI_37));

const double m[7]={
    4.970684,
    0.646926,
    3.228604,
    3.587895,
    1.225946,
    1.666555,
    7.35522e-01
};
const double L_xx[7]={
    7.0337e-01,
    7.9620e-03,
    3.7242e-02,
    2.5853e-02,
    3.5549e-02,
    1.9640e-03, 
    1.2516e-02
};
const double L_yy[7]={
    7.0661e-01, 
    2.8110e-02, 
    3.6155e-02,
    1.9552e-02, 
    2.9474e-02,
    4.3540e-03, 
    1.0027e-02
};
const double L_zz[7]={
    9.1170e-03,
    2.5995e-02,
    1.0830e-02,
    2.8323e-02,
    8.6270e-03,
    5.4330e-03,
    4.8150e-03
};
const double L_xy[7]={
    -1.3900e-04,
    -3.9250e-03,
    -4.7610e-03,
    7.7960e-03, 
    -2.1170e-03,
    1.0900e-04, 
    -4.2800e-04
};
const double L_xz[7]={
     6.7720e-03, 
     1.0254e-02, 
    -1.1396e-02,
    -1.3320e-03, 
    -4.0370e-03,
    -1.1580e-03, 
    -1.1960e-03
};
const double L_yz[7]={
    1.9169e-02, 
    7.0400e-04, 
    -1.2805e-02,
    8.6410e-03, 
    2.2900e-04,
    3.4100e-04, 
    -7.4100e-04
};
const double c_x[7]={
    3.875e-03,
    -3.141e-03,
    2.7518e-02,
    -5.317e-02,
    -1.1953e-02,
    6.0149e-02,
    1.0517e-02
};
const double c_y[7]={
    2.081e-03,
    -2.872e-02,
    3.9252e-02,
    1.04419e-01,
    4.1065e-02,
    -1.4117e-02,
    -4.252e-03
};
const double c_z[7]={
    -0.175,//这个是另一种方法得出的。。
    3.495e-03,
    -6.6502e-02,
    2.7454e-02,
    -3.8437e-02,
    -1.0517e-02,
    6.1597e-02
};
const double l_x[7]={
    c_x[0]*m[0],
    c_x[1]*m[1],
    c_x[2]*m[2],
    c_x[3]*m[3],
    c_x[4]*m[4],
    c_x[5]*m[5],
    c_x[6]*m[6],
};
const double l_y[7]={
    c_y[0]*m[0],
    c_y[1]*m[1],
    c_y[2]*m[2],
    c_y[3]*m[3],
    c_y[4]*m[4],
    c_y[5]*m[5],
    c_y[6]*m[6],
};
const double l_z[7]={
    c_z[0]*m[0],
    c_z[1]*m[1],
    c_z[2]*m[2],
    c_z[3]*m[3],
    c_z[4]*m[4],
    c_z[5]*m[5],
    c_z[6]*m[6],
};
const double f_v[7]={
    0.0665,     
    0.1987,
    0.0399,
    0.2257, 
    0.1023,
    -0.0132,
    0.0638
};
const double f_c[7]={
    0.245,      
    0.1523,     
    0.1827, 
    0.3591,   
    0.2669, 
    0.1658, 
    0.2109   
};
const double f_o[7]={
    -0.1073,
    -0.1566,
    -0.0686,
    -0.2522,
    0.0045,
    0.0910,
    -0.0127
};


//   paramsF<<
//   7.0337e-01, -1.3900e-04, 6.7720e-03, 7.0661e-01, 1.9169e-02, 9.1170e-03,3.875e-03*m[0],2.081e-03*m[0],-0.175*m[0],m[0],0.0665,0.245,           
//   7.9620e-03, -3.9250e-03, 1.0254e-02, 2.8110e-02, 7.0400e-04, 2.5995e-02,-3.141e-03*m[1],-2.872e-02*m[1],3.495e-03*m[1],m[1],0.1987,0.1523,      
//   3.7242e-02, -4.7610e-03, -1.1396e-02, 3.6155e-02, -1.2805e-02, 1.0830e-02,2.7518e-02*m[2],3.9252e-02*m[2],-6.6502e-02*m[2],m[2],0.0399,0.1827,  
//   2.5853e-02, 7.7960e-03, -1.3320e-03, 1.9552e-02, 8.6410e-03, 2.8323e-02,-5.317e-02*m[3],1.04419e-01*m[3],2.7454e-02*m[3],m[3],0.2257,0.3591,   
//   3.5549e-02, -2.1170e-03, -4.0370e-03, 2.9474e-02, 2.2900e-04, 8.6270e-03,-1.1953e-02*m[4],4.1065e-02*m[4],-3.8437e-02*m[4],m[4],0.1023,0.2669,   
//   1.9640e-03, 1.0900e-04, -1.1580e-03, 4.3540e-03, 3.4100e-04, 5.4330e-03,6.0149e-02*m[5],-1.4117e-02*m[5],-1.0517e-02*m[5],m[5],-0.0132,0.1658,  
//   1.2516e-02, -4.2800e-04, -1.1960e-03, 1.0027e-02, -7.4100e-04, 4.8150e-03,1.0517e-02*m[6],-4.252e-03*m[6],6.1597e-02*m[6],m[6],0.0638,0.2109   
//   ; 
// const double params[84]={
// 7.0337e-01, -1.3900e-04, 6.7720e-03, 7.0661e-01, 1.9169e-02, 9.1170e-03,3.875e-03*m[0],2.081e-03*m[0],-0.175*m[0],m[0],0,0,
// 7.9620e-03, -3.9250e-03, 1.0254e-02, 2.8110e-02, 7.0400e-04, 2.5995e-02,-3.141e-03*m[1],-2.872e-02*m[1],3.495e-03*m[1],m[1],0,0,
// 3.7242e-02, -4.7610e-03, -1.1396e-02, 3.6155e-02, -1.2805e-02, 1.0830e-02,2.7518e-02*m[2],3.9252e-02*m[2],-6.6502e-02*m[2],m[2],0,0,
// 2.5853e-02, 7.7960e-03, -1.3320e-03, 1.9552e-02, 8.6410e-03, 2.8323e-02,-5.317e-02*m[3],1.04419e-01*m[3],2.7454e-02*m[3],m[3],0,0,
// 3.5549e-02, -2.1170e-03, -4.0370e-03, 2.9474e-02, 2.2900e-04, 8.6270e-03,-1.1953e-02*m[4],4.1065e-02*m[4],-3.8437e-02*m[4],m[4],0,0,
// 1.9640e-03, 1.0900e-04, -1.1580e-03, 4.3540e-03, 3.4100e-04, 5.4330e-03,6.0149e-02*m[5],-1.4117e-02*m[5],-1.0517e-02*m[5],m[5],0,0,
// 1.2516e-02, -4.2800e-04, -1.1960e-03, 1.0027e-02, -7.4100e-04, 4.8150e-03,1.0517e-02*m[6],-4.252e-03*m[6],6.1597e-02*m[6],m[6],0,0
// };
Eigen::Matrix7_7 MassMatrix(const Eigen::Vector7_1 &q);

Eigen::Matrix7_7 CoriolisMatrix(const Eigen::Vector7_1 &q,const Eigen::Vector7_1 &dq);

Eigen::Vector7_1 GravityVector(const Eigen::Vector7_1 &q);

Eigen::Vector7_1 Friction(const Eigen::Vector7_1 &dq);


Eigen::Matrix7_7 C_Panda(const Eigen::Vector91_1 &parms,const Eigen::Vector7_1 &q, const Eigen::Vector7_1 &dq);

Eigen::Matrix7_7 M_Panda(const Eigen::Vector91_1 &parms,const Eigen::Vector7_1 &q);

Eigen::Vector7_1 G_Panda(const Eigen::Vector91_1 &parms,const Eigen::Vector7_1 &q);

Eigen::Vector7_1 F_Panda(const Eigen::Vector91_1 &parms,const Eigen::Vector7_1 &dq);

Eigen::Matrix7_91 Regressor_Panda(const Eigen::Vector7_1 &q, const Eigen::Vector7_1 &dq, const Eigen::Vector7_1 &ddq);

Eigen::Matrix7_91 Slotine_Panda(const Eigen::Vector7_1 &q, const Eigen::Vector7_1 &dq, const Eigen::Vector7_1 &v,const Eigen::Vector7_1 &dv);

Eigen::Matrix7_64 Base_Regressor_Panda(const Eigen::Vector7_1 &q, const Eigen::Vector7_1 &dq, const Eigen::Vector7_1 &ddq);

Eigen::Matrix7_64 Base_Slotine_Panda(const Eigen::Vector7_1 &q, const Eigen::Vector7_1 &q_dot, const Eigen::Vector7_1 &qr_dot,const Eigen::Vector7_1 &qr_ddot);

Eigen::Matrix7_64 Base_Regressor_Panda_noG(const Eigen::Vector7_1 &q, const Eigen::Vector7_1 &dq, const Eigen::Vector7_1 &ddq);

Eigen::Matrix7_64 Base_Slotine_Panda_noG(const Eigen::Vector7_1 &q, const Eigen::Vector7_1 &q_dot, const Eigen::Vector7_1 &qr_dot,const Eigen::Vector7_1 &qr_ddot);

Eigen::Matrix7_43 Regressor43_Panda(const Eigen::Vector7_1 &q, const Eigen::Vector7_1 &dq, const Eigen::Vector7_1 &ddq);

Eigen::Matrix7_43 Slotine43_Panda(const Eigen::Vector7_1 &q, const Eigen::Vector7_1 &q_dot, const Eigen::Vector7_1 &qr_dot,const Eigen::Vector7_1 &qr_ddot);


Eigen::Matrix7_64 Base_Regressor_Fiction_Panda(const Eigen::Vector7_1 &dq);

Eigen::Matrix<double, 7, 64> base_regressor_without_fiction(const Eigen::Matrix<double, 7, 1> &q,
                                                            const Eigen::Matrix<double, 7, 1> &q_dot,
                                                            const Eigen::Matrix<double, 7, 1> &q_ddot);

/*
废弃的84参数的
*/
// Eigen::Matrix7_7 C_Panda(const Eigen::Vector84_1 &parms,const Eigen::Vector7_1 &q, const Eigen::Vector7_1 &dq);

// Eigen::Matrix7_7 M_Panda(const Eigen::Vector84_1 &parms,const Eigen::Vector7_1 &q);

// Eigen::Vector7_1 G_Panda(const Eigen::Vector84_1 &parms,const Eigen::Vector7_1 &q);

// Eigen::Vector7_1 F_Panda(const Eigen::Vector84_1 &parms,const Eigen::Vector7_1 &dq);


// Eigen::Matrix7_84 regressor_Panda_84_2F(const Eigen::Vector7_1 &q, const Eigen::Vector7_1 &dq, const Eigen::Vector7_1 &ddq);

// Eigen::Matrix7_84 slotine_panda_84_2F(const Eigen::Vector7_1 &q, const Eigen::Vector7_1 &dq, const Eigen::Vector7_1 &v,const Eigen::Vector7_1 &dv);


#endif /* INCLUDE_FRANKA_MODEL_H_ */