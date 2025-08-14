//  Copyright (c) 2020 Franka Emika GmbH - All Rights Reserved
//  This file is subject to the terms and conditions defined in the file
//  'LICENSE' , which is part of this package

#include <string.h>
#include <vector>

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <map>

#include <Poco/Path.h>

#include <franka/exception.h>
#include <franka/robot.h>

#include "examples_common.h"

#include "robot_api.h"
#include "gripper_api.h"

SimulinkPandaRobot::SimulinkPandaRobot() = default;

SimulinkPandaRobot::SimulinkPandaRobot(const char * robotIPmask,
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
                                       const int elbowControlMask){
    
    parseMaskSettings(robotIPmask,
                      gripperAttachedMask,
                      controlModeMask,
                      controllerChoiceMask,
                      collisionThresholdsMask,
                      jointImpedanceMask,
                      cartesianImpedanceMask,
                      loadInertiaMask,
                      EE_T_KMask, 
                      initialJointConfigurationRequestedMask,
                      initialJointConfigurationMask,
                      elbowControlMask);
    
    
    controlThreadHasBeenSpawned = false;    
    controlThreadStepDone = false;
    terminateControlThread = false; 
    controlThreadException = false;
    inputsHaveBeenCopied = false;
    
    bool computationalPriorityIsFigured = false;
    
    currentlyInFirstControlStep = true;
    
    setControlModeMembersBegin();
    
    robot = std::make_unique<franka::Robot>(robotIPString);
    
    robotModel = std::make_unique<franka::Model>(robot->loadModel());
}

SimulinkPandaRobot& SimulinkPandaRobot::operator=(SimulinkPandaRobot&& otherSimulinkPandaRobot){
    
    if (this == &otherSimulinkPandaRobot) return *this;
    
    robotIPString = std::move(otherSimulinkPandaRobot.robotIPString);
    
    gripperAttached = otherSimulinkPandaRobot.gripperAttached;
    controlMode = otherSimulinkPandaRobot.controlMode;
    initialJointConfigurationRequested = otherSimulinkPandaRobot.initialJointConfigurationRequested;
    elbowControl = otherSimulinkPandaRobot.elbowControl;
    
    collisionThresholds = std::move(otherSimulinkPandaRobot.collisionThresholds);
    jointImpedance = std::move(otherSimulinkPandaRobot.jointImpedance);
    cartesianImpedance = std::move(otherSimulinkPandaRobot.cartesianImpedance);
    loadInertia = std::move(otherSimulinkPandaRobot.loadInertia);
    EE_T_KK = std::move(otherSimulinkPandaRobot.EE_T_KK);
    initialJointConfiguration = std::move(otherSimulinkPandaRobot.initialJointConfiguration);
    
    controlThreadHasBeenSpawned = false;    
    controlThreadStepDone = false;
    terminateControlThread = false; 
    controlThreadException = false;
    inputsHaveBeenCopied = false;
    
    bool computationalPriorityIsFigured = false;
    
    currentlyInFirstControlStep = true;
    
    setControlModeMembersBegin();
    
    robot = std::make_unique<franka::Robot>(robotIPString);
    
    robotModel = std::make_unique<franka::Model>(robot->loadModel());
    
    return *this;
    
}

SimulinkPandaRobot::~SimulinkPandaRobot(){
    
    terminateControlThread = true;
    controlThreadStepDone = true;

    // notify control thread that the inputs have been read
    notifyControlThreadToContinue();
    
};
                                                     
void SimulinkPandaRobot::parseMaskSettings(const char * robotIPmask,
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
                                           const int elbowControlMask){
    
    // robot_ip_
    robotIPString.assign(robotIPmask); 
    
    // gripperAttached
    gripperAttached = gripperAttachedMask;
  
    // control mode
    controlMode = controlModeMask;

    // controller_choice
    controllerMode = (franka::ControllerMode)controllerChoiceMask;

    // collision_thresholds
    std::copy(collisionThresholdsMask,
              collisionThresholdsMask + 52, collisionThresholds.data());
   
    // joint_impedance
    std::copy(jointImpedanceMask,
              jointImpedanceMask + 7, jointImpedance.data());

    // cartesian_impedance
    std::copy(cartesianImpedanceMask,
              cartesianImpedanceMask + 6, cartesianImpedance.data());

    // load_inertia
    std::copy(loadInertiaMask,
              loadInertiaMask + 13, loadInertia.data());

    // EE_T_KK
    std::copy(EE_T_KMask,
              EE_T_KMask + 16, EE_T_KK.data());

    // init_joint_configuration_req
    initialJointConfigurationRequested = initialJointConfigurationRequestedMask;

    // init_joint_configuration
    std::copy(initialJointConfigurationMask,
              initialJointConfigurationMask + 7, initialJointConfiguration.data());

    // elbow control requested in case of cartesian pose or velocity is commanded.
    elbowControl = elbowControlMask;

    // control mode
    if ((bool)elbowControl) {
        switch (controlMode) {
          case torqueControlCartesianPose:
            controlMode = torqueControlCartesianPoseWithElbow;
            break;

          case torqueControlCartesianVelocities:
            controlMode = torqueControlCartesianVelocitiesWithElbow;
            break;

          case cartesianPoseControllerMode:
            controlMode = cartesianPoseControllerModeWithElbow;
            break;

          case cartesianVelocitiesControllerMode:
            controlMode = cartesianVelocitiesControllerModeWithElbow;
            break;
        }
    }
    
}

void SimulinkPandaRobot::applyCollisionBehaviorSettings() {
    std::array<double, 7> lowerTorqueThresholdsAcceleration;
    std::copy(collisionThresholds.begin(), collisionThresholds.begin() + 7,
              lowerTorqueThresholdsAcceleration.data());

    std::array<double, 7> upperTorqueThresholdsAcceleration;
    std::copy(collisionThresholds.begin() + 7, collisionThresholds.begin() + 14,
              upperTorqueThresholdsAcceleration.data());

    std::array<double, 7> lowerTorqueThresholdsNominal;
    std::copy(collisionThresholds.begin() + 14, collisionThresholds.begin() + 21,
              lowerTorqueThresholdsNominal.data());

    std::array<double, 7> upperTorqueThresholdsNominal;
    std::copy(collisionThresholds.begin() + 21, collisionThresholds.begin() + 28,
              lowerTorqueThresholdsNominal.data());

    std::array<double, 6> lowerForceThresholdsAcceleration;
    std::copy(collisionThresholds.begin() + 28, collisionThresholds.begin() + 34,
              lowerForceThresholdsAcceleration.data());

    std::array<double, 6> upperForceThresholdsAcceleration;
    std::copy(collisionThresholds.begin() + 34, collisionThresholds.begin() + 40,
              upperForceThresholdsAcceleration.data());

    std::array<double, 6> lowerForceThresholdsNominal;
    std::copy(collisionThresholds.begin() + 40, collisionThresholds.begin() + 46,
              lowerForceThresholdsNominal.data());

    std::array<double, 6> upperForceThresholdsNominal;
    std::copy(collisionThresholds.begin() + 46, collisionThresholds.begin() + 52,
              upperForceThresholdsNominal.data());

    robot->setCollisionBehavior(
        lowerTorqueThresholdsAcceleration, upperTorqueThresholdsAcceleration,
        lowerTorqueThresholdsNominal, upperTorqueThresholdsNominal,
        lowerForceThresholdsAcceleration, upperForceThresholdsAcceleration,
        lowerForceThresholdsNominal, upperForceThresholdsNominal);
}

void SimulinkPandaRobot::applyRobotSettings() {
    // Is Initial Configuration Requested
    if (initialJointConfigurationRequested) {
        setDefaultBehavior(*robot);   
        MotionGenerator motionGenerator(0.5, initialJointConfiguration);
        robot->control(motionGenerator);
    }

  // Load Robot Parameters

  // 1. Collision thresholds
  applyCollisionBehaviorSettings();
  robot->setJointImpedance(jointImpedance);

  // 3. Cartesian Impedance setCartesianImpedance
  robot->setCartesianImpedance(cartesianImpedance);
  
  // 4.
  robot->setK(EE_T_KK);

  // 6.
  std::array<double, 3> loadCenterOfMass;
  std::copy(loadInertia.begin() + 1, loadInertia.begin() + 4, loadCenterOfMass.data());

  std::array<double, 9> inertiaMatrix;
  std::copy(loadInertia.begin() + 4, loadInertia.begin() + 13, inertiaMatrix.data());

  robot->setLoad(loadInertia[0], loadCenterOfMass, inertiaMatrix);
}

// Map correlating strings reffering to robot state members with their corresponding vector sizes.
const double* SimulinkPandaRobot::getRobotStateSignalPointerForStringLiteral(const std::string& signalNameString) {
   
        if (signalNameString.compare("O_T_EE") == 0)
            return robotState.O_T_EE.data();
        else if (signalNameString.compare("O_T_EE_d") == 0)
            return robotState.O_T_EE_d.data();
        else if (signalNameString.compare("F_T_EE") == 0)
            return robotState.F_T_EE.data();
        else if (signalNameString.compare("EE_T_K") == 0)
            return robotState.EE_T_K.data();
        else if (signalNameString.compare("m_ee") == 0)
            return &robotState.m_ee;
        else if (signalNameString.compare("I_ee") == 0)
            return robotState.I_ee.data();
        else if (signalNameString.compare("F_x_Cee") == 0)
            return robotState.F_x_Cee.data();
        else if (signalNameString.compare("m_load") == 0)
            return &robotState.m_load;
        else if (signalNameString.compare("I_load") == 0)
            return robotState.I_load.data();
        else if (signalNameString.compare("F_x_Cload") == 0)
            return robotState.F_x_Cload.data();
        else if (signalNameString.compare("m_total") == 0)
            return &robotState.m_total;
        else if (signalNameString.compare("I_total") == 0)
            return robotState.I_total.data();
        else if (signalNameString.compare("F_x_Ctotal") == 0)
            return robotState.F_x_Ctotal.data();
        else if (signalNameString.compare("elbow") == 0)
            return robotState.elbow.data();
        else if (signalNameString.compare("elbow_d") == 0)
            return robotState.elbow_d.data();
        else if (signalNameString.compare("elbow_c") == 0)
            return robotState.elbow_c.data();
        else if (signalNameString.compare("delbow_c") == 0)
            return robotState.delbow_c.data();         
        else if (signalNameString.compare("ddelbow_c") == 0)
            return robotState.ddelbow_c.data();
        else if (signalNameString.compare("tau_J") == 0)
            return robotState.tau_J.data();
        else if (signalNameString.compare("tau_J_d") == 0)
            return robotState.tau_J_d.data();
        else if (signalNameString.compare("dtau_J") == 0)
            return robotState.dtau_J.data();
        else if (signalNameString.compare("q") == 0)
            return robotState.q.data();
        else if (signalNameString.compare("q_d") == 0)
            return robotState.q_d.data();
        else if (signalNameString.compare("dq") == 0)
            return robotState.dq.data();
        else if (signalNameString.compare("dq_d") == 0)
            return robotState.dq_d.data();
        else if (signalNameString.compare("ddq_d") == 0)
            return robotState.ddq_d.data();
        else if (signalNameString.compare("joint_contact") == 0)
            return robotState.joint_contact.data();
        else if (signalNameString.compare("cartesian_contact") == 0)
            return robotState.cartesian_contact.data();
        else if (signalNameString.compare("joint_collision") == 0)
            return robotState.joint_collision.data();
        else if (signalNameString.compare("cartesian_collision") == 0)
            return robotState.cartesian_collision.data();
        else if (signalNameString.compare("tau_ext_hat_filtered") == 0)
            return robotState.tau_ext_hat_filtered.data();
        else if (signalNameString.compare("O_F_ext_hat_K") == 0)
            return robotState.O_F_ext_hat_K.data();
        else if (signalNameString.compare("K_F_ext_hat_K") == 0)
            return robotState.K_F_ext_hat_K.data();
        else if (signalNameString.compare("O_dP_EE_d") == 0)
            return robotState.O_dP_EE_d.data();
        else if (signalNameString.compare("O_T_EE_c") == 0)
            return robotState.O_T_EE_c.data();
        else if (signalNameString.compare("O_dP_EE_c") == 0)
            return robotState.O_dP_EE_c.data();
        else if (signalNameString.compare("O_ddP_EE_c") == 0)
            return robotState.O_ddP_EE_c.data();
        else if (signalNameString.compare("theta") == 0)
            return robotState.theta.data();
        else if (signalNameString.compare("dtheta") == 0)
            return robotState.dtheta.data();     
        else if (signalNameString.compare("control_command_success_rate") == 0)
            return &robotState.control_command_success_rate;            
}

void SimulinkPandaRobot::setControlModeMembersBegin() {
    
        controlModeMembersBegin[0].memberBegin[0] = controllerInputs.tau_J_d.data();
        
        controlModeMembersBegin[1].memberBegin[0] = controllerInputs.q_d.data();
        controlModeMembersBegin[1].memberBegin[1] = controllerInputs.tau_J_d.data();
        
        controlModeMembersBegin[2].memberBegin[0] = controllerInputs.q_d.data();
        controlModeMembersBegin[2].memberBegin[1] = controllerInputs.tau_J_d.data();
            
        controlModeMembersBegin[3].memberBegin[0] = controllerInputs.O_T_EE_d.data();
        controlModeMembersBegin[3].memberBegin[1] = controllerInputs.tau_J_d.data();
        
        controlModeMembersBegin[4].memberBegin[0] = controllerInputs.O_dP_EE_d.data();
        controlModeMembersBegin[4].memberBegin[1] = controllerInputs.tau_J_d.data();

        controlModeMembersBegin[5].memberBegin[0] = controllerInputs.q_d.data();
        
        controlModeMembersBegin[6].memberBegin[0] = controllerInputs.dq_d.data();
        
        controlModeMembersBegin[7].memberBegin[0] = controllerInputs.O_T_EE_d.data();
        
        controlModeMembersBegin[8].memberBegin[0] = controllerInputs.O_dP_EE_d.data();
        
        controlModeMembersBegin[9].memberBegin[0] = controllerInputs.O_T_EE_d.data();
        controlModeMembersBegin[9].memberBegin[1] = controllerInputs.elbow_d.data();
        controlModeMembersBegin[9].memberBegin[2] = controllerInputs.tau_J_d.data();
        
        controlModeMembersBegin[10].memberBegin[0] = controllerInputs.O_dP_EE_d.data();
        controlModeMembersBegin[10].memberBegin[1] = controllerInputs.elbow_d.data();
        controlModeMembersBegin[10].memberBegin[2] = controllerInputs.tau_J_d.data();
        
        controlModeMembersBegin[11].memberBegin[0] = controllerInputs.O_T_EE_d.data();
        controlModeMembersBegin[11].memberBegin[1] = controllerInputs.elbow_d.data();
        
        controlModeMembersBegin[12].memberBegin[0] = controllerInputs.O_dP_EE_d.data();
        controlModeMembersBegin[12].memberBegin[1] = controllerInputs.elbow_d.data();
        
}

int SimulinkPandaRobot::establishIfCurrentBlockFirstToBeComputed(){
    if (!computationalPriorityIsFigured) {
        computationalPriorityIsFigured = true;
        return 1;
    } else {
        return 0;
    }
}

void SimulinkPandaRobot::checkIfAndHandleException(){  
    if (controlThreadException) {
      throw std::runtime_error("Execution terminated due to exception thrown during robot control!\n");
      return;
    }
}

void SimulinkPandaRobot::notifyControlThreadToContinue(){
    if (!currentlyInFirstControlStep) {
        std::unique_lock<std::mutex> lk2(mutexForEnsuringCurrentStepStepControlSignal);
        inputsHaveBeenCopied = true;
        lk2.unlock();
        conditionVariableForEnsuringCurrentStepStepControlSignal.notify_one();
    }
}

void SimulinkPandaRobot::waitForControlThreadStep(){ 
    std::unique_lock<std::mutex> lk(mutexForMainControlStepCycle);
    conditionVariableForMainControlStepCycle.wait(lk, [&] { return controlThreadStepDone; });
    controlThreadStepDone = false;
}

void SimulinkPandaRobot::notifyMainThreadToContinue()
{
    std::unique_lock<std::mutex> lk(mutexForMainControlStepCycle);
    controlThreadStepDone = true;
    lk.unlock();
    conditionVariableForMainControlStepCycle.notify_one(); 
}

void SimulinkPandaRobot::waitNotificationFromMainThreadToContinue()
{
    std::unique_lock<std::mutex> lk2(mutexForEnsuringCurrentStepStepControlSignal);
    conditionVariableForEnsuringCurrentStepStepControlSignal.wait(lk2, [&]{return inputsHaveBeenCopied;});
    inputsHaveBeenCopied = false;
}

extern void (*controlModeCallbackFunction[13])(SimulinkPandaRobot& simulinkPandaRobot);

void SimulinkPandaRobot::spawnControlThread(){
    
    // Spawn the corresponding control thread
    controlThread = std::thread(controlModeCallbackFunction[controlMode], std::ref(*this));

//     sched_param sch;
//     int policy;
//     pthread_getschedparam(controlThread.native_handle(), &policy, &sch);
//     sch.sched_priority = 1;
//     if (pthread_setschedparam(controlThread.native_handle(), SCHED_FIFO, &sch)) {
//       throw std::runtime_error("Failure to apply control thread configuration!\n");
//       return;
//     }
    controlThread.detach();
    controlThreadHasBeenSpawned = true;
}

void SimulinkPandaRobot::copyInputSignal(double *inputSignal, int inputSignalIndex){
    
     std::copy(inputSignal,
               inputSignal + controlModeSizes[controlMode].width[inputSignalIndex - gripperAttached],
               (double*)controlModeMembersBegin[controlMode].memberBegin[inputSignalIndex - gripperAttached]);
     
}

void SimulinkPandaRobot::copyOutputSignal(std::vector<std::string>& outputSignalsStack, int outputSignalIndex, double *outputSignal ){
    std::copy(
          getRobotStateSignalPointerForStringLiteral(outputSignalsStack.at(outputSignalIndex)),
          getRobotStateSignalPointerForStringLiteral(outputSignalsStack.at(outputSignalIndex)) + getWidthForSignalString[outputSignalsStack.at(outputSignalIndex)],
          outputSignal);
}

bool SimulinkPandaRobot::getControlThreadHasBeenSpawned() const{
    return controlThreadHasBeenSpawned;
}

void SimulinkPandaRobot::setSampleTime(double currentSampleTime){
    sampleTime = currentSampleTime;
}

double SimulinkPandaRobot::getSampleTime() const{
    return sampleTime;
}

int SimulinkPandaRobot::getElbowControl() const{
    return elbowControl;
}

void SimulinkPandaRobot::mountRobotState(const franka::RobotState& currentRobotState){
    robotState = currentRobotState;
}

const franka::RobotState SimulinkPandaRobot::getRobotState(){
    return robotState;
}

void SimulinkPandaRobot::copyRobotPose(double *outputSignal){
    std::array<double, 16> pose = robotModel->pose(franka::Frame::kEndEffector, robotState);
    std::copy(pose.begin(), pose.end(), outputSignal);
}

void SimulinkPandaRobot::copyBodyJacobian(double *outputSignal){
    std::array<double, 42> pose = robotModel->bodyJacobian(franka::Frame::kEndEffector, robotState);
    std::copy(pose.begin(), pose.end(), outputSignal);
}

void SimulinkPandaRobot::copyZeroJacobian(double *outputSignal){
    std::array<double, 42> pose = robotModel->zeroJacobian(franka::Frame::kEndEffector, robotState);
    std::copy(pose.begin(), pose.end(), outputSignal);
}

void SimulinkPandaRobot::copyMass(double *outputSignal){
    std::array<double, 49> pose = robotModel->mass(robotState);
    std::copy(pose.begin(), pose.end(), outputSignal);
}

void SimulinkPandaRobot::copyCoriolis(double *outputSignal){
    std::array<double, 7> pose = robotModel->coriolis(robotState);
    std::copy(pose.begin(), pose.end(), outputSignal);
}

void SimulinkPandaRobot::copyGravity(double *outputSignal){
    std::array<double, 7> pose = robotModel->gravity(robotState);
    std::copy(pose.begin(), pose.end(), outputSignal);
}

void SimulinkPandaRobot::setCurrentlyInFirstControlStep(bool controlStepFlag){
    currentlyInFirstControlStep = controlStepFlag;
}

bool SimulinkPandaRobot::getCurrentlyInFirstControlStep() const{
    return currentlyInFirstControlStep;
}

bool SimulinkPandaRobot::getTerminateControlThread() const{
    return terminateControlThread;
}

franka::ControllerMode SimulinkPandaRobot::getControllerMode() const{
    return controllerMode;
}

void SimulinkPandaRobot::setControlThreadExceptionFlag(){
    controlThreadException = true; 
}

std::array<double, 7> const &SimulinkPandaRobot::getControllerInputTorques() const{
    return controllerInputs.tau_J_d;
};
std::array<double, 7> const &SimulinkPandaRobot::getControllerInputJointPositions() const{
    return controllerInputs.q_d;
};
std::array<double, 7> const &SimulinkPandaRobot::getControllerInputJointVelocities() const{
    return controllerInputs.dq_d;
};
std::array<double, 16> const &SimulinkPandaRobot::getControllerInputCartesianPose() const{
    return controllerInputs.O_T_EE_d;
};
std::array<double, 6> const &SimulinkPandaRobot::getControllerInputCartesianVelocities() const{
    return controllerInputs.O_dP_EE_d;
};
std::array<double, 2> const &SimulinkPandaRobot::getControllerInputElbowPosition() const{
    return controllerInputs.elbow_d;
};
