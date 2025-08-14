//  Copyright (c) 2021 Franka Emika GmbH - All Rights Reserved
//  This file is subject to the terms and conditions defined in the file
//  'LICENSE' , which is part of this package

#include <math.h>
#include <iostream>
#include "mex.h"
#include <chrono>
#include <thread>

#ifdef _WIN32 
#include <corecrt_math_defines.h>
#endif

#include <franka/duration.h>
#include <franka/exception.h>
#include <franka/robot.h>

#include "examples_common.h"

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) {
  /* Check for proper number of arguments */
  if (nrhs != 1) {
    mexErrMsgIdAndTxt("MATLAB:franka_communication_test:nargin", 
            "robot's ip string is required as input.");
  } 

  size_t mrows = mxGetM(prhs[0]);
  size_t ncols = mxGetN(prhs[0]);
  if (mxIsChar(prhs[0]) != 1) {
      mexErrMsgIdAndTxt("MATLAB:franka_communication_test:inputNoString",
                        "robot's ip argument as string is required.");
  }

  if(nlhs > 1){
      mexErrMsgIdAndTxt( "MATLAB:franka_communication_test:maxlhs",
            "Too many output arguments.");
  }

  //Assign field names
  const char* field_names[] = {
      "test_result",
      "lost_robot_states",
      "avg_success_rate",
      "min_success_rate",
      "max_success_rate",
      "counter"
  };

  /* Create a 1-by-n array of structs. */
  mwSize dims[1] = {1};
  plhs[0] = mxCreateStructArray(1, dims, 6, field_names);

  // Define states & Allocate memory
  mxArray* test_result_out = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxArray* lost_robot_states_out = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxArray* avg_success_rate_out = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxArray* min_success_rate_out = mxCreateDoubleMatrix(1, 1, mxREAL); 
  mxArray* max_success_rate_out = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxArray* counter_out = mxCreateDoubleMatrix(1, 1, mxREAL);

  /* Parse robot's ip string */
  size_t buflen = mxGetN(prhs[0]) + 1;
  char* robot_ip = (char*)mxCalloc(buflen, sizeof(char));
  mxGetString(prhs[0], robot_ip, (mwSize)buflen);
  
  enum test_results { FAIL, SUCCESS};

  // test stats to be returned
  bool test_result = SUCCESS;
  uint64_t lost_robot_states = 0;
  double avg_success_rate = 0.0;
  double min_success_rate = 1.0;
  double max_success_rate = 0.0;
  uint64_t counter = 0;

  uint64_t time = 0;
  
  try {
    franka::Robot robot(robot_ip);
    setDefaultBehavior(robot);

    // First move the robot to a suitable joint configuration
    std::array<double, 7> q_goal = {{0, -M_PI_4, 0, -3 * M_PI_4, 0, M_PI_2, M_PI_4}};
    MotionGenerator motion_generator(0.5, q_goal);
    robot.control(motion_generator);

    robot.setCollisionBehavior(
        {{20.0, 20.0, 18.0, 18.0, 16.0, 14.0, 12.0}}, {{20.0, 20.0, 18.0, 18.0, 16.0, 14.0, 12.0}},
        {{20.0, 20.0, 18.0, 18.0, 16.0, 14.0, 12.0}}, {{20.0, 20.0, 18.0, 18.0, 16.0, 14.0, 12.0}},
        {{20.0, 20.0, 20.0, 25.0, 25.0, 25.0}}, {{20.0, 20.0, 20.0, 25.0, 25.0, 25.0}},
        {{20.0, 20.0, 20.0, 25.0, 25.0, 25.0}}, {{20.0, 20.0, 20.0, 25.0, 25.0, 25.0}});

    franka::Torques zero_torques{{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}};
    robot.control(
        [&time, &counter, &avg_success_rate, &min_success_rate, &max_success_rate, zero_torques](
            const franka::RobotState& robot_state, franka::Duration period) -> franka::Torques {
          time += period.toMSec();
          if (time == 0.0) {
            return zero_torques;
          }
          counter++;

          std::this_thread::sleep_for(std::chrono::microseconds(100));

          avg_success_rate += robot_state.control_command_success_rate;
          if (robot_state.control_command_success_rate > max_success_rate) {
            max_success_rate = robot_state.control_command_success_rate;
          }
          if (robot_state.control_command_success_rate < min_success_rate) {
            min_success_rate = robot_state.control_command_success_rate;
          }

          if (time >= 10000) {
            return franka::MotionFinished(zero_torques);
          }

          return zero_torques;
        },
        false, 1000);
  } catch (franka::Exception const& e) {
    mexErrMsgIdAndTxt("MATLAB:franka_communication_test:communicationTestFailed", e.what());
  }
  avg_success_rate = avg_success_rate / counter;

  lost_robot_states = time - counter;

  if (avg_success_rate < 0.90) {
    test_result = FAIL;
  }

  // assign output
  *mxGetPr(test_result_out) = test_result;
  *mxGetPr(lost_robot_states_out) = (double)lost_robot_states;
  *mxGetPr(avg_success_rate_out) = avg_success_rate;
  *mxGetPr(min_success_rate_out) = min_success_rate;
  *mxGetPr(max_success_rate_out) = max_success_rate;
  *mxGetPr(counter_out) = (double)counter;

  mxSetField(plhs[0],0,"test_result",test_result_out);
  mxSetField(plhs[0],0,"lost_robot_states",lost_robot_states_out);
  mxSetField(plhs[0],0,"avg_success_rate",avg_success_rate_out);
  mxSetField(plhs[0],0,"min_success_rate",min_success_rate_out);
  mxSetField(plhs[0],0,"max_success_rate",max_success_rate_out);
  mxSetField(plhs[0],0,"counter",counter_out);

  mxFree(robot_ip);
  return;
}