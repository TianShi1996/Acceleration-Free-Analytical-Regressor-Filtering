//  Copyright (c) 2020 Franka Emika GmbH - All Rights Reserved
//  This file is subject to the terms and conditions defined in the file
//  'LICENSE' , which is part of this package

#ifndef SIZES_CODEGEN_H
#define SIZES_CODEGEN_H

#include <string.h>
#include <vector>
#include <map>

#include "structs.h"

typedef enum {torqueControl,
              torqueControlJointPositions,
              torqueControlJointVelocities,
              torqueControlCartesianPose,
              torqueControlCartesianVelocities,
              jointPositionsControllerMode,
              jointVelocitiesControllerMode,
              cartesianPoseControllerMode,
              cartesianVelocitiesControllerMode,
              torqueControlCartesianPoseWithElbow,
              torqueControlCartesianVelocitiesWithElbow,
              cartesianPoseControllerModeWithElbow,
              cartesianVelocitiesControllerModeWithElbow
} controlModesType;

extern controlModesType controlModes;
extern std::map<std::string, int> getWidthForSignalString;                                                    
extern struct ControlModeSizes controlModeSizes[13];                                    
void replaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);
void signalsStringToSignalsVector(std::vector<std::string>& signals, const char* signalsString);
                                                                             
#endif