//  Copyright (c) 2021 Franka Emika GmbH - All Rights Reserved
//  This file is subject to the terms and conditions defined in the file
//  'LICENSE' , which is part of this package

#include <string.h>
#include "mex.h"
#include "matrix.h"
#include <iostream>

#include <franka/exception.h>
#include <franka/robot.h>

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) {
  /* Check for proper number of arguments */
  if (nrhs != 1) {
    mexErrMsgIdAndTxt("MATLAB:franka_robot_state:nargin", 
            "robot's ip string is required as input.");
  }

  size_t mrows = mxGetM(prhs[0]);
  size_t ncols = mxGetN(prhs[0]);
  if (mxIsChar(prhs[0]) != 1) {
      mexErrMsgIdAndTxt("MATLAB:franka_robot_state:inputNoString",
                        "robot's ip argument as string is required.");
  }

  if(nlhs > 1){
      mexErrMsgIdAndTxt( "MATLAB:franka_robot_state:maxlhs",
            "Too many output arguments.");
  }
  
  /* Prepare output structure*/
  
  //Assign field names
  const char* field_names[] = {
      "O_T_EE",
      "O_T_EE_d",
      "F_T_EE",
      "F_T_NE",
      "NE_T_EE",
      "EE_T_K",
      "m_ee",
      "I_ee",
      "F_x_Cee",
      "m_load",
      "I_load",
      "F_x_Cload",
      "m_total",
      "I_total",
      "F_x_Ctotal",
      "elbow",
      "elbow_d",
      "elbow_c",
      "delbow_c",
      "ddelbow_c",
      "tau_J",
      "tau_J_d",
      "dtau_J",
      "q",
      "q_d",
      "dq",
      "dq_d",
      "ddq_d",
      "joint_contact",
      "cartesian_contact",
      "joint_collision",
      "cartesian_collision",
      "tau_ext_hat_filtered",
      "O_F_ext_hat_K",
      "K_F_ext_hat_K",
      "O_dP_EE_d",
      "O_T_EE_c",
      "O_dP_EE_c",
      "O_ddP_EE_c",
      "theta",
      "dtheta",
      "current_errors",
      "last_motion_errors",
      "control_command_success_rate"
  };
  
  /* Create a 1-by-n array of structs. */
  mwSize dims[1] = {1};
  plhs[0] = mxCreateStructArray(1, dims, 44, field_names);

  /* Parse robot's ip string */
  size_t buflen = mxGetN(prhs[0]) + 1;
  char* robot_ip = (char*)mxCalloc(buflen, sizeof(char));
  mxGetString(prhs[0], robot_ip, (mwSize)buflen);

  // Define states & Allocate memory
  mxArray* O_T_EE = mxCreateDoubleMatrix(4, 4, mxREAL);
  mxArray* O_T_EE_d = mxCreateDoubleMatrix(4, 4, mxREAL);
  mxArray* F_T_EE = mxCreateDoubleMatrix(4, 4, mxREAL);
  mxArray* F_T_NE = mxCreateDoubleMatrix(4, 4, mxREAL); 
  mxArray* NE_T_EE = mxCreateDoubleMatrix(4, 4, mxREAL);
  mxArray* EE_T_K = mxCreateDoubleMatrix(4, 4, mxREAL); 
  mxArray* m_ee = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxArray* I_ee = mxCreateDoubleMatrix(3, 3, mxREAL); 
  mxArray* F_x_Cee = mxCreateDoubleMatrix(3, 1, mxREAL);
  mxArray* m_load = mxCreateDoubleMatrix(1, 1, mxREAL);   
  mxArray* I_load = mxCreateDoubleMatrix(3, 3, mxREAL);
  mxArray* F_x_Cload = mxCreateDoubleMatrix(3, 1, mxREAL);
  mxArray* m_total = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxArray* I_total = mxCreateDoubleMatrix(3, 3, mxREAL); 
  mxArray* F_x_Ctotal = mxCreateDoubleMatrix(3, 1, mxREAL);
  mxArray* elbow = mxCreateDoubleMatrix(2, 1, mxREAL); 
  mxArray* elbow_d = mxCreateDoubleMatrix(2, 1, mxREAL);
  mxArray* elbow_c = mxCreateDoubleMatrix(2, 1, mxREAL); 
  mxArray* delbow_c = mxCreateDoubleMatrix(2, 1, mxREAL);
  mxArray* ddelbow_c = mxCreateDoubleMatrix(2, 1, mxREAL); 
  mxArray* tau_J = mxCreateDoubleMatrix(7, 1, mxREAL);
  mxArray* tau_J_d = mxCreateDoubleMatrix(7, 1, mxREAL);
  mxArray* dtau_J = mxCreateDoubleMatrix(7, 1, mxREAL);
  mxArray* q = mxCreateDoubleMatrix(7, 1, mxREAL); 
  mxArray* q_d = mxCreateDoubleMatrix(7, 1, mxREAL);
  mxArray* dq = mxCreateDoubleMatrix(7, 1, mxREAL); 
  mxArray* dq_d = mxCreateDoubleMatrix(7, 1, mxREAL);
  mxArray* ddq_d = mxCreateDoubleMatrix(7, 1, mxREAL); 
  mxArray* joint_contact = mxCreateDoubleMatrix(7, 1, mxREAL);
  mxArray* cartesian_contact = mxCreateDoubleMatrix(6, 1, mxREAL);
  mxArray* joint_collision = mxCreateDoubleMatrix(7, 1, mxREAL);
  mxArray* cartesian_collision = mxCreateDoubleMatrix(6, 1, mxREAL); 
  mxArray* tau_ext_hat_filtered = mxCreateDoubleMatrix(7, 1, mxREAL);
  mxArray* O_F_ext_hat_K = mxCreateDoubleMatrix(6, 1, mxREAL); 
  mxArray* K_F_ext_hat_K = mxCreateDoubleMatrix(6, 1, mxREAL);
  mxArray* O_dP_EE_d = mxCreateDoubleMatrix(6, 1, mxREAL); 
  mxArray* O_T_EE_c = mxCreateDoubleMatrix(4, 4, mxREAL);
  mxArray* O_dP_EE_c = mxCreateDoubleMatrix(6, 1, mxREAL); 
  mxArray* O_ddP_EE_c = mxCreateDoubleMatrix(6, 1, mxREAL);
  mxArray* theta = mxCreateDoubleMatrix(7, 1, mxREAL);
  mxArray* dtheta = mxCreateDoubleMatrix(7, 1, mxREAL);
  mxArray* current_errors;
  mxArray* last_motion_errors;
  mxArray* control_command_success_rate = mxCreateDoubleMatrix(1, 1, mxREAL);
  
  try {  
    /* Connect to the robot and read it's current state  */
    franka::Robot robot = franka::Robot(robot_ip);
    
    robot.read([&](const franka::RobotState& franka_robot_state) {
      
      // Copy the actual values robot ==> matlab!
      std::copy(std::begin(franka_robot_state.O_T_EE), std::end(franka_robot_state.O_T_EE), mxGetPr(O_T_EE));
      std::copy(std::begin(franka_robot_state.O_T_EE_d), std::end(franka_robot_state.O_T_EE_d), mxGetPr(O_T_EE_d));
      std::copy(std::begin(franka_robot_state.F_T_EE), std::end(franka_robot_state.F_T_EE), mxGetPr(F_T_EE));
      std::copy(std::begin(franka_robot_state.F_T_NE), std::end(franka_robot_state.F_T_NE), mxGetPr(F_T_NE));
      std::copy(std::begin(franka_robot_state.NE_T_EE), std::end(franka_robot_state.NE_T_EE), mxGetPr(NE_T_EE));
      std::copy(std::begin(franka_robot_state.EE_T_K), std::end(franka_robot_state.EE_T_K), mxGetPr(EE_T_K));
      *mxGetPr(m_ee) = franka_robot_state.m_ee;
      std::copy(std::begin(franka_robot_state.I_ee), std::end(franka_robot_state.I_ee), mxGetPr(I_ee));
      std::copy(std::begin(franka_robot_state.F_x_Cee), std::end(franka_robot_state.F_x_Cee), mxGetPr(F_x_Cee));
      *mxGetPr(m_load) = franka_robot_state.m_load;
      std::copy(std::begin(franka_robot_state.I_load), std::end(franka_robot_state.I_load), mxGetPr(I_load));
      std::copy(std::begin(franka_robot_state.F_x_Cload), std::end(franka_robot_state.F_x_Cload), mxGetPr(F_x_Cload));
      *mxGetPr(m_total) = franka_robot_state.m_total;
      std::copy(std::begin(franka_robot_state.I_total), std::end(franka_robot_state.I_total), mxGetPr(I_total));
      std::copy(std::begin(franka_robot_state.F_x_Ctotal), std::end(franka_robot_state.F_x_Ctotal), mxGetPr(F_x_Ctotal));
      std::copy(std::begin(franka_robot_state.elbow), std::end(franka_robot_state.elbow), mxGetPr(elbow));
      std::copy(std::begin(franka_robot_state.elbow_d), std::end(franka_robot_state.elbow_d), mxGetPr(elbow_d));
      std::copy(std::begin(franka_robot_state.elbow_c), std::end(franka_robot_state.elbow_c), mxGetPr(elbow_c));
      std::copy(std::begin(franka_robot_state.delbow_c), std::end(franka_robot_state.delbow_c), mxGetPr(delbow_c));
      std::copy(std::begin(franka_robot_state.ddelbow_c), std::end(franka_robot_state.ddelbow_c), mxGetPr(ddelbow_c));
      std::copy(std::begin(franka_robot_state.tau_J), std::end(franka_robot_state.tau_J), mxGetPr(tau_J));
      std::copy(std::begin(franka_robot_state.tau_J_d), std::end(franka_robot_state.tau_J_d), mxGetPr(tau_J_d));
      std::copy(std::begin(franka_robot_state.dtau_J), std::end(franka_robot_state.dtau_J), mxGetPr(dtau_J));
      std::copy(std::begin(franka_robot_state.q), std::end(franka_robot_state.q), mxGetPr(q));
      std::copy(std::begin(franka_robot_state.q_d), std::end(franka_robot_state.q_d), mxGetPr(q_d));
      std::copy(std::begin(franka_robot_state.dq), std::end(franka_robot_state.dq), mxGetPr(dq));
      std::copy(std::begin(franka_robot_state.dq_d), std::end(franka_robot_state.dq_d), mxGetPr(dq_d));
      std::copy(std::begin(franka_robot_state.ddq_d), std::end(franka_robot_state.ddq_d), mxGetPr(ddq_d));
      std::copy(std::begin(franka_robot_state.joint_contact), std::end(franka_robot_state.joint_contact), mxGetPr(joint_contact));
      std::copy(std::begin(franka_robot_state.cartesian_contact), std::end(franka_robot_state.cartesian_contact), mxGetPr(cartesian_contact));
      std::copy(std::begin(franka_robot_state.joint_collision), std::end(franka_robot_state.joint_collision), mxGetPr(joint_collision));
      std::copy(std::begin(franka_robot_state.cartesian_collision), std::end(franka_robot_state.cartesian_collision), mxGetPr(cartesian_collision));
      std::copy(std::begin(franka_robot_state.tau_ext_hat_filtered), std::end(franka_robot_state.tau_ext_hat_filtered), mxGetPr(tau_ext_hat_filtered));
      std::copy(std::begin(franka_robot_state.O_F_ext_hat_K), std::end(franka_robot_state.O_F_ext_hat_K), mxGetPr(O_F_ext_hat_K));
      std::copy(std::begin(franka_robot_state.K_F_ext_hat_K), std::end(franka_robot_state.K_F_ext_hat_K), mxGetPr(K_F_ext_hat_K));
      std::copy(std::begin(franka_robot_state.O_dP_EE_d), std::end(franka_robot_state.O_dP_EE_d), mxGetPr(O_dP_EE_d));
      std::copy(std::begin(franka_robot_state.O_T_EE_c), std::end(franka_robot_state.O_T_EE_c), mxGetPr(O_T_EE_c));
      std::copy(std::begin(franka_robot_state.O_dP_EE_c), std::end(franka_robot_state.O_dP_EE_c), mxGetPr(O_dP_EE_c));
      std::copy(std::begin(franka_robot_state.O_ddP_EE_c), std::end(franka_robot_state.O_ddP_EE_c), mxGetPr(O_ddP_EE_c));
      std::copy(std::begin(franka_robot_state.theta), std::end(franka_robot_state.theta), mxGetPr(theta));
      std::copy(std::begin(franka_robot_state.dtheta), std::end(franka_robot_state.dtheta), mxGetPr(dtheta));
      current_errors = mxCreateString(std::string(franka_robot_state.current_errors).c_str());
      last_motion_errors = mxCreateString(std::string(franka_robot_state.last_motion_errors).c_str());
      *mxGetPr(control_command_success_rate) = franka_robot_state.control_command_success_rate;
      
      return false;
    });
  } catch (franka::Exception const& e) {
      mexErrMsgIdAndTxt("MATLAB:franka_robot_state:robotStateCommandFailed", e.what());
  }

  //Assign the field values
  mxSetField(plhs[0],0,"O_T_EE",O_T_EE);
  mxSetField(plhs[0],0,"O_T_EE_d",O_T_EE_d);
  mxSetField(plhs[0],0,"F_T_EE",F_T_EE);
  mxSetField(plhs[0],0,"F_T_NE",F_T_NE);
  mxSetField(plhs[0],0,"NE_T_EE",NE_T_EE);
  mxSetField(plhs[0],0,"EE_T_K",EE_T_K);
  mxSetField(plhs[0],0,"m_ee",m_ee);
  mxSetField(plhs[0],0,"I_ee",I_ee);
  mxSetField(plhs[0],0,"F_x_Cee",F_x_Cee);
  mxSetField(plhs[0],0,"m_load",m_load);
  mxSetField(plhs[0],0,"I_load",I_load);
  mxSetField(plhs[0],0,"F_x_Cload",F_x_Cload);
  mxSetField(plhs[0],0,"m_total",m_total);
  mxSetField(plhs[0],0,"I_total",I_total);
  mxSetField(plhs[0],0,"F_x_Ctotal",F_x_Ctotal);
  mxSetField(plhs[0],0,"elbow",elbow);
  mxSetField(plhs[0],0,"elbow_d",elbow_d);
  mxSetField(plhs[0],0,"elbow_c",elbow_c);
  mxSetField(plhs[0],0,"delbow_c",delbow_c);
  mxSetField(plhs[0],0,"ddelbow_c",ddelbow_c);
  mxSetField(plhs[0],0,"tau_J",tau_J);
  mxSetField(plhs[0],0,"tau_J_d",tau_J_d);
  mxSetField(plhs[0],0,"dtau_J",dtau_J);
  mxSetField(plhs[0],0,"q",q);
  mxSetField(plhs[0],0,"q_d",q_d);
  mxSetField(plhs[0],0,"dq",dq);
  mxSetField(plhs[0],0,"dq_d",dq_d);
  mxSetField(plhs[0],0,"ddq_d",ddq_d);
  mxSetField(plhs[0],0,"joint_contact",joint_contact);
  mxSetField(plhs[0],0,"cartesian_contact",cartesian_contact);
  mxSetField(plhs[0],0,"joint_collision",joint_collision);
  mxSetField(plhs[0],0,"cartesian_collision",cartesian_collision);
  mxSetField(plhs[0],0,"tau_ext_hat_filtered",tau_ext_hat_filtered);
  mxSetField(plhs[0],0,"O_F_ext_hat_K",O_F_ext_hat_K);
  mxSetField(plhs[0],0,"K_F_ext_hat_K",K_F_ext_hat_K);
  mxSetField(plhs[0],0,"O_dP_EE_d",O_dP_EE_d);
  mxSetField(plhs[0],0,"O_T_EE_c",O_T_EE_c);
  mxSetField(plhs[0],0,"O_dP_EE_c",O_dP_EE_c);
  mxSetField(plhs[0],0,"O_ddP_EE_c",O_ddP_EE_c);
  mxSetField(plhs[0],0,"theta",theta);
  mxSetField(plhs[0],0,"dtheta",dtheta);
  mxSetField(plhs[0],0,"current_errors",current_errors);
  mxSetField(plhs[0],0,"last_motion_errors",last_motion_errors);
  mxSetField(plhs[0],0,"control_command_success_rate",control_command_success_rate);

  mxFree(robot_ip);
  return;
}