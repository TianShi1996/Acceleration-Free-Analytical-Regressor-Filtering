//  Copyright (c) 2020 Franka Emika GmbH - All Rights Reserved
//  This file is subject to the terms and conditions defined in the file
//  'LICENSE' , which is part of this package

#ifndef ROBOT_API_H
#define ROBOT_API_H

#include <string.h>
#include <vector>

#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <map>

#include <Poco/Path.h>

#include <franka/exception.h>
#include <franka/gripper.h>
#include <franka/robot.h>
#include <franka/model.h>

#include "sizes_codegen.h"

#include "structs.h"

#include "examples_common.h"
       
class SimulinkPandaRobot{
    
    // Mask Parameters

    std::string robotIPString;
    
    int gripperAttached;
    int controlMode;
    int initialJointConfigurationRequested;
    int elbowControl;
    
    std::array<double, 52> collisionThresholds;
    std::array<double, 7> jointImpedance;
    std::array<double, 6> cartesianImpedance;
    std::array<double, 13> loadInertia;
    std::array<double, 16> EE_T_KK;
    std::array<double, 7> initialJointConfiguration;

    franka::RobotState robotState;
    std::unique_ptr<franka::Model> robotModel;
            
    franka::ControllerMode controllerMode;
    
    bool currentlyInFirstControlStep;
    bool computationalPriorityIsFigured;
    
    bool terminateControlThread;
    bool controlThreadException;
    
    double sampleTime;
         
    struct ControllerInputsStruct controllerInputs;
    
    struct ControlModeMembersBegin controlModeMembersBegin[13];
    
    std::thread controlThread;
    
    bool controlThreadHasBeenSpawned;
    
    std::mutex mutexForMainControlStepCycle;
    std::mutex mutexForEnsuringCurrentStepStepControlSignal;
    
    std::condition_variable conditionVariableForMainControlStepCycle;
    std::condition_variable conditionVariableForEnsuringCurrentStepStepControlSignal;
    
    bool controlThreadStepDone;
    bool inputsHaveBeenCopied;
    
public:
    
    std::unique_ptr<franka::Robot> robot;
    
    SimulinkPandaRobot();
    
    SimulinkPandaRobot(const char * robotIPmask,
                       const int gripperAttachedMask,
                       const int controlModeMask,
                       const int controllerChoiceMask,
                       const double *collisionThresholdsMask,
                       const double *jointImpedanceMask,
                       const double *cartesianImpedanceMask,
                       const double *loadInertiaMask,
                       const double *EE_T_KMask, 
                       const int initialJointConfigurationRequestedMask,
                       const double *initialJointConfigurationMask,
                       const int elbowControlMask);
    
    SimulinkPandaRobot& operator=(SimulinkPandaRobot&& otherSimulinkPandaRobot);
    
    ~SimulinkPandaRobot();
    
    void parseMaskSettings(const char * robotIPmask,
                           const int gripperAttachedMask,
                           const int controlModeMask,
                           const int controllerChoiceMask,
                           const double *collisionThresholdsMask,
                           const double *jointImpedanceMask,
                           const double *cartesianImpedanceMask,
                           const double *loadInertiaMask,
                           const double *EE_T_KMask, 
                           const int initialJointConfigurationRequestedMask,
                           const double *initialJointConfigurationMask,
                           const int elbowControlMask);
    
    void applyCollisionBehaviorSettings();
    void applyRobotSettings();
    int establishIfCurrentBlockFirstToBeComputed();
    
    void checkIfAndHandleException();
    void setControlModeMembersBegin();
    const double* getRobotStateSignalPointerForStringLiteral(const std::string& signalNameString);
    
    void copyInputSignal(double *inputSignal, int inputSignalIndex);
    void copyOutputSignal(std::vector<std::string>& outputSignalsStack, int outputSignalIndex, double *outputSignal);
    
    void spawnControlThread();
    void notifyControlThreadToContinue();
    void waitForControlThreadStep();
    void notifyMainThreadToContinue();
    void waitNotificationFromMainThreadToContinue();
    
    void mountRobotState(const franka::RobotState& currentRobotState);
    const franka::RobotState getRobotState();
    
    bool getControlThreadHasBeenSpawned() const;
    bool getCurrentlyInFirstControlStep() const;
    
    void setSampleTime(double currentSampleTime);
    double getSampleTime() const;
    int getElbowControl() const;
    
    void copyRobotPose(double *outputSignal);
    void copyBodyJacobian(double *outputSignal);
    void copyZeroJacobian(double *outputSignal);
    void copyMass(double *outputSignal);
    void copyCoriolis(double *outputSignal);
    void copyGravity(double *outputSignal);
    
    void setCurrentlyInFirstControlStep(bool controlStepFlag);
    void setControlThreadExceptionFlag();
    
    bool getTerminateControlThread() const;
    franka::ControllerMode getControllerMode() const;
    
    std::array<double, 7> const &getControllerInputTorques() const;
    std::array<double, 7> const &getControllerInputJointPositions() const;
    std::array<double, 7> const &getControllerInputJointVelocities() const;
    std::array<double, 16> const &getControllerInputCartesianPose() const;
    std::array<double, 6> const &getControllerInputCartesianVelocities() const;
    std::array<double, 2> const &getControllerInputElbowPosition() const;
      
};

#endif