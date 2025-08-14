//  Copyright (c) 2021 Franka Emika GmbH - All Rights Reserved
//  This file is subject to the terms and conditions defined in the file
//  'LICENSE' , which is part of this package

#include <math.h>
#include <iostream>
#include "mex.h"

#include <franka/exception.h>
#include <franka/robot.h>

#include "examples_common.h"

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) {
  /* Check for proper number of arguments */
  if (nrhs != 3) {
    mexErrMsgIdAndTxt("MATLAB:franka_joint_point_to_point_motion:nargin",
            "Usage: \n\
            >>franka_joint_point_to_point_motion(robot-hostname, q_goal, speed_factor)\n\
            q_goal is a 7x1 array with the joint angles in [rad].\n\
            speed-factor must be between zero and one.");    
  }
  if (nlhs > 1) {
    mexErrMsgIdAndTxt("MATLAB:franka_joint_point_to_point_motion:nargout",
            "no output argument is provided.");
  }

  plhs[0] = mxCreateDoubleMatrix((mwSize)1, (mwSize)1, mxREAL);
  *mxGetPr(plhs[0]) = 1;

  /* Parse robot's ip string */
  size_t buflen = mxGetN(prhs[0]) + 1;
  char* robot_ip = (char*)mxCalloc(buflen, sizeof(char));
  mxGetString(prhs[0], robot_ip, (mwSize)buflen);
  
  /* Parse the q_goal */
  mwSize q_goal_nel = mxGetNumberOfElements(prhs[1]);
  if (q_goal_nel != 7) {
    mexErrMsgIdAndTxt("MATLAB:franka_joint_point_to_point_motion:qGoalInputError",
            "The q_goal needs to be 7x1 array");
  }
  std::array<double, 7> q_goal;
  for (size_t i = 0; i < 7; i++) {
    q_goal[i] = mxGetPr(prhs[1])[i];
  }
  
  /* Parse the speed_factor */
  mwSize speed_factor_nel = mxGetNumberOfElements(prhs[2]);
  if (speed_factor_nel != 1) {
    mexErrMsgIdAndTxt("MATLAB:franka_joint_point_to_point_motion:speedFactorInputError",
            "The speed factor needs to be scalar");
  }
  double speed_factor = mxGetScalar(prhs[2]);

  try {
    /* Connect to the robot and move to the desired configuration */
    franka::Robot robot(robot_ip);
    setDefaultBehavior(robot);

    // Set additional parameters always before the control loop, NEVER in the control loop!
    // Set collision behavior.
    robot.setCollisionBehavior(
        {{20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0}}, {{20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0}},
        {{10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0}}, {{10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0}},
        {{20.0, 20.0, 20.0, 20.0, 20.0, 20.0}}, {{20.0, 20.0, 20.0, 20.0, 20.0, 20.0}},
        {{10.0, 10.0, 10.0, 10.0, 10.0, 10.0}}, {{10.0, 10.0, 10.0, 10.0, 10.0, 10.0}});

    MotionGenerator motion_generator(speed_factor, q_goal);
    robot.control(motion_generator);
  } catch (franka::Exception const& e) {
    mexErrMsgIdAndTxt("MATLAB:franka_joint_point_to_point_motion:robotStateCommandFailed", e.what());
  }
  mxFree(robot_ip);
  return;
}