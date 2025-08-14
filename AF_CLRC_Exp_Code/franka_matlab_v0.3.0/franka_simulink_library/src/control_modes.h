//  Copyright (c) 2020 Franka Emika GmbH - All Rights Reserved
//  This file is subject to the terms and conditions defined in the file
//  'LICENSE' , which is part of this package

#ifndef CONTROL_MODES_H
#define CONTROL_MODES_H

#include <string.h>

#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "robot_api.h"

#include <franka/exception.h>
#include <franka/robot.h>

void controlTorque(SimulinkPandaRobot& simulinkPandaRobot);
void controlTorqueJointPositions(SimulinkPandaRobot& simulinkPandaRobot);
void controlTorqueJointVelocities(SimulinkPandaRobot& simulinkPandaRobot);
void controlTorqueCartesianPose(SimulinkPandaRobot& simulinkPandaRobot);
void controlTorqueCartesianVelocities(SimulinkPandaRobot& simulinkPandaRobot);
void controlJointPositionsControllerMode(SimulinkPandaRobot& simulinkPandaRobot);
void controlJointVelocitiesControllerMode(SimulinkPandaRobot& simulinkPandaRobot);
void controlCartesianPoseControllerMode(SimulinkPandaRobot& simulinkPandaRobot);
void controlCartesianVelocitiesControllerMode(SimulinkPandaRobot& simulinkPandaRobot);
void controlTorqueCartesianVelocitiesWithElbow(SimulinkPandaRobot& simulinkPandaRobot);
void controlTorqueCartesianPoseWithElbow(SimulinkPandaRobot& simulinkPandaRobot);
void controlCartesianPoseControllerModeWithElbow(SimulinkPandaRobot& simulinkPandaRobot);
void controlCartesianVelocitiesControllerModeWithElbow(SimulinkPandaRobot& simulinkPandaRobot);

extern void (*controlModeCallbackFunction[13])(SimulinkPandaRobot& simulinkPandaRobot);

#endif