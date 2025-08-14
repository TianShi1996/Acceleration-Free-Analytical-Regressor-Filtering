//  Copyright (c) 2020 Franka Emika GmbH - All Rights Reserved
//  This file is subject to the terms and conditions defined in the file
//  'LICENSE' , which is part of this package

#include <string.h>

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

#include "robot_api.h"
#include "control_modes_utils.h"

#include <franka/exception.h>
#include <franka/robot.h>

template <typename controllerType>
controllerType standardControlLogic(const franka::RobotState& robotState,
                                       franka::Duration period, SimulinkPandaRobot& simulinkPandaRobot) {
  // fetch the current sample time
  simulinkPandaRobot.setSampleTime(period.toSec());
  
  // update robot state
  simulinkPandaRobot.mountRobotState(robotState);
 
  // first step flag set
  simulinkPandaRobot.setCurrentlyInFirstControlStep(false);
  
  // notify mdlOutput that we are entering major control step
  simulinkPandaRobot.notifyMainThreadToContinue();
  
  // wait till mdlOutput has copied the inputs
  simulinkPandaRobot.waitNotificationFromMainThreadToContinue();

  if (simulinkPandaRobot.getTerminateControlThread()) {
    return franka::MotionFinished(handlingParseInfo<controllerType>(simulinkPandaRobot));
  }
  
  return handlingParseInfo<controllerType>(simulinkPandaRobot);
}

template <typename controllerType>
void applyControlWithTwoObjectives(SimulinkPandaRobot& simulinkPandaRobot) {
  simulinkPandaRobot.robot->control(
      [&](const franka::RobotState& robotState, franka::Duration period) -> franka::Torques {
        if (simulinkPandaRobot.getTerminateControlThread()) {
          return franka::MotionFinished(handlingParseInfo<franka::Torques>(simulinkPandaRobot));
        }
        return handlingParseInfo<franka::Torques>(simulinkPandaRobot);;
      },
      [&](const franka::RobotState& robotState, franka::Duration period) -> controllerType {
        if (simulinkPandaRobot.getTerminateControlThread()) {
          return franka::MotionFinished(handlingParseInfo<controllerType>(simulinkPandaRobot));
        }
        return standardControlLogic<controllerType>(robotState, period,simulinkPandaRobot);
      });
}

template <typename controllerType>
void applyControl(SimulinkPandaRobot& simulinkPandaRobot) {
  simulinkPandaRobot.robot->control(
      [&](const franka::RobotState& robotState, franka::Duration period) -> controllerType {
        if (simulinkPandaRobot.getTerminateControlThread()) {
          return franka::MotionFinished(handlingParseInfo<controllerType>(simulinkPandaRobot));
        }
        return standardControlLogic<controllerType>(robotState, period,simulinkPandaRobot);
      },
      simulinkPandaRobot.getControllerMode());
}

template <>
void applyControl<franka::Torques>(SimulinkPandaRobot& simulinkPandaRobot) {
  simulinkPandaRobot.robot->control(
      [&](const franka::RobotState& robotState, franka::Duration period) -> franka::Torques {
        return standardControlLogic<franka::Torques>(robotState, period,simulinkPandaRobot);
      });
}

void exceptionHandle(const franka::Exception& e, SimulinkPandaRobot& simulinkPandaRobot) {
  
  simulinkPandaRobot.setControlThreadExceptionFlag();
  simulinkPandaRobot.notifyMainThreadToContinue();
  std::cout << e.what() << std::endl;
}

void standardTryCatchFunc(void (*robotControl)(SimulinkPandaRobot&), SimulinkPandaRobot& simulinkPandaRobot) {
  try {
    robotControl(simulinkPandaRobot);
  } catch (const franka::Exception& e) {
    exceptionHandle(e,simulinkPandaRobot);
  }
}

void controlTorque(SimulinkPandaRobot& simulinkPandaRobot) {
  standardTryCatchFunc(applyControl<franka::Torques>, simulinkPandaRobot);
}

void controlTorqueJointPositions(SimulinkPandaRobot& simulinkPandaRobot) {
  standardTryCatchFunc(applyControlWithTwoObjectives<franka::JointPositions>, simulinkPandaRobot);
}

void controlTorqueJointVelocities(SimulinkPandaRobot& simulinkPandaRobot) {
  standardTryCatchFunc(applyControlWithTwoObjectives<franka::JointVelocities>, simulinkPandaRobot);
}

void controlTorqueCartesianPose(SimulinkPandaRobot& simulinkPandaRobot) {
  standardTryCatchFunc(applyControlWithTwoObjectives<franka::CartesianPose>, simulinkPandaRobot);
}

void controlTorqueCartesianVelocities(SimulinkPandaRobot& simulinkPandaRobot) {
  standardTryCatchFunc(applyControlWithTwoObjectives<franka::CartesianVelocities>, simulinkPandaRobot);
}

void controlJointPositionsControllerMode(SimulinkPandaRobot& simulinkPandaRobot) {
  standardTryCatchFunc(applyControl<franka::JointPositions>, simulinkPandaRobot);
}

void controlJointVelocitiesControllerMode(SimulinkPandaRobot& simulinkPandaRobot) {
  standardTryCatchFunc(applyControl<franka::JointVelocities>, simulinkPandaRobot);
}

void controlCartesianPoseControllerMode(SimulinkPandaRobot& simulinkPandaRobot) {
  standardTryCatchFunc(applyControl<franka::CartesianPose>, simulinkPandaRobot);
}

void controlCartesianVelocitiesControllerMode(SimulinkPandaRobot& simulinkPandaRobot) {
  standardTryCatchFunc(applyControl<franka::CartesianVelocities>, simulinkPandaRobot);
}

void (*controlModeCallbackFunction[13])(SimulinkPandaRobot& simulinkPandaRobot) = { controlTorque,
                                                                                    controlTorqueJointPositions,
                                                                                    controlTorqueJointVelocities,
                                                                                    controlTorqueCartesianPose,
                                                                                    controlTorqueCartesianVelocities,
                                                                                    controlJointPositionsControllerMode,
                                                                                    controlJointVelocitiesControllerMode,
                                                                                    controlCartesianPoseControllerMode,
                                                                                    controlCartesianVelocitiesControllerMode,
                                                                                    controlTorqueCartesianVelocities,
                                                                                    controlTorqueCartesianPose,
                                                                                    controlCartesianPoseControllerMode,
                                                                                    controlCartesianVelocitiesControllerMode};
