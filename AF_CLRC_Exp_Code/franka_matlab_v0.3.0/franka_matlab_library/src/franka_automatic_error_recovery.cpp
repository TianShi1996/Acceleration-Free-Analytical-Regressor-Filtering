//  Copyright (c) 2020 Franka Emika GmbH - All Rights Reserved
//  This file is subject to the terms and conditions defined in the file
//  'LICENSE' , which is part of this package

#include <math.h>
#include <iostream>
#include "mex.h"

#include <franka/exception.h>
#include <franka/robot.h>

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) {
  /* Check for proper number of arguments */
  if (nrhs != 1) {
    mexErrMsgIdAndTxt("MATLAB:franka_automatic_error_recovery:nargin", 
            "robot's ip string is required as input.");
  }

  size_t mrows = mxGetM(prhs[0]);
  size_t ncols = mxGetN(prhs[0]);
  if (mxIsChar(prhs[0]) != 1) {
      mexErrMsgIdAndTxt("MATLAB:franka_automatic_error_recovery:inputNoString",
                        "robot's ip argument as string is required.");
  }

  if (nlhs > 1) {
    mexErrMsgIdAndTxt("MATLAB:franka_automatic_error_recovery:nargout",
                      "Too many output arguments.");
  }
  
  /* Parse robot's ip string */
  size_t buflen = mxGetN(prhs[0]) + 1;
  char* robot_ip = (char*)mxCalloc(buflen, sizeof(char));
  mxGetString(prhs[0], robot_ip, (mwSize)buflen);

  plhs[0] = mxCreateDoubleMatrix((mwSize)1, (mwSize)1, mxREAL);
  *mxGetPr(plhs[0]) = 1;
  
  try {
    /* Connect to the robot and apply automatic error recovery */
    franka::Robot robot = franka::Robot(robot_ip);
    robot.automaticErrorRecovery();

  } catch (franka::Exception const& e) {
    mexErrMsgIdAndTxt("MATLAB:franka_automatic_error_recovery:communicationTestFailed",e.what());
  }
  mxFree(robot_ip);
  return;
}