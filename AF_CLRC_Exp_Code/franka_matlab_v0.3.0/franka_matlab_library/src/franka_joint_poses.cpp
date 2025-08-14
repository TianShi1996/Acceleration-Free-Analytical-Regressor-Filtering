//  Copyright (c) 2021 Franka Emika GmbH - All Rights Reserved
//  This file is subject to the terms and conditions defined in the file
//  'LICENSE' , which is part of this package

#include <math.h>
#include <iostream>
#include <iterator>
#include "mex.h"

#include <franka/exception.h>
#include <franka/model.h>

template <class T, size_t N>
std::ostream& operator<<(std::ostream& ostream, const std::array<T, N>& array) {
  ostream << "[";
  std::copy(array.cbegin(), array.cend() - 1, std::ostream_iterator<T>(ostream, ","));
  std::copy(array.cend() - 1, array.cend(), std::ostream_iterator<T>(ostream));
  ostream << "]";
  return ostream;
}

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) {
  /* Check for proper number of arguments */
  if (nrhs != 1) {
    mexErrMsgIdAndTxt("MATLAB:franka_joint_poses:nargin", 
            "robot's ip string is required as input.");
  }

  size_t mrows = mxGetM(prhs[0]);
  size_t ncols = mxGetN(prhs[0]);
  if (mxIsChar(prhs[0]) != 1) {
      mexErrMsgIdAndTxt("MATLAB:franka_joint_poses:inputNoString",
                        "robot's ip argument as string is required.");
  }

  if (nlhs > 1) {
    mexErrMsgIdAndTxt("MATLAB:franka_joint_poses:nargout", 
            "no output argument is provided.");
  }

  static const int no_frames = 10;
  mxArray *frame_matrix[no_frames];

  mwSize dims[1];
  mwSize ndim;

  size_t frame_mrows = 4;
  size_t frame_ncols = 4;

  /* create a cell array for output  */
  ndim = 1; // 10 frames
  dims[0] = no_frames;
  plhs[0] = mxCreateCellArray(ndim, dims);

  /* Parse robot's ip string */
  size_t buflen = mxGetN(prhs[0]) + 1;
  char* robot_ip = (char*)mxCalloc(buflen, sizeof(char));
  mxGetString(prhs[0], robot_ip, (mwSize)buflen);

  // allocate mem for frames to be returned
  for (int i=0; i<no_frames; i++){
    frame_matrix[i] = mxCreateDoubleMatrix((mwSize)frame_mrows, (mwSize)frame_ncols, mxREAL);
  }
  
  try {
    /* Connect to the robot and print it's current joint poses  */
    franka::Robot robot(robot_ip);
    franka::RobotState state = robot.readOnce();
    franka::Model model(robot.loadModel());

    int i = 0;
    for (franka::Frame frame = franka::Frame::kJoint1; frame <= franka::Frame::kStiffness;
         frame++) {
      std::array<double,16> jp(model.pose(frame, state));
      std::copy(std::begin(jp), std::end(jp), mxGetPr(frame_matrix[i]));
      mxSetCell(plhs[0], i, mxDuplicateArray(frame_matrix[i]));
      i++;
    }
  } catch (franka::Exception const& e) {
    mexErrMsgIdAndTxt("MATLAB:franka_joint_poses:jointPosesCommandFailed", e.what());
  }
  mxFree(robot_ip);
  return;
}