#include "gripper_api.h"
#include <franka/gripper.h>

SimulinkPandaGripper::SimulinkPandaGripper(const char * robotIPMask){
    
  robotIP.assign(robotIPMask); 
  
  terminateGripperThread = false;
  gripperCurrentControlMode = idle_;
  
  gripper = std::make_unique<franka::Gripper>(robotIP);
  gripperControlThread = std::thread(&gripperControlThread_func, std::ref(*this));
  
  // toggle first time to notify the sim model that the gripper is ready to receive commands
  updateCommandCounter();
  {
    std::unique_lock<std::mutex> lk(m);
    gripperCommandApplied = true;
    lk.unlock();
    cv.notify_one();
  }
}

bool SimulinkPandaGripper::gripperControlRequested() {
  if (triggerGripperCommand > triggerGripperCommandPrev) {
    triggerGripperCommandPrev = triggerGripperCommand;
    return true;
  } else {
    return false;
  }
}

SimulinkPandaGripper::~SimulinkPandaGripper(){
    
  terminateGripperThread = true;

  gripperCurrentControlMode = idle_;
  // notify gripper control thread that the inputs have been read
  {
    std::unique_lock<std::mutex> lk(m);
    gripperCommandApplied = true;
    lk.unlock();
    cv.notify_one();
  }

  if (gripperControlThread.joinable()) {
    gripperControlThread.join();
  }       
}

void SimulinkPandaGripper::parseGripperCommand(double *gripperCommandVector){
    
  gripperCurrentControlMode = (int)gripperCommandVector[0];
  triggerGripperCommand = (int)gripperCommandVector[1];
  graspWidth = (double)gripperCommandVector[2];
  graspSpeed = (double)gripperCommandVector[3];
  graspForce = (double)gripperCommandVector[4];
  graspEpsilonInner = (double)gripperCommandVector[5];
  graspEpsilonOuter = (double)gripperCommandVector[6];
  moveWidth = (double)gripperCommandVector[7];
  moveSpeed = (double)gripperCommandVector[8];
    
}

void SimulinkPandaGripper::applyGripperCommand(){
    
  if (gripperControlRequested()) {
    {
      std::unique_lock<std::mutex> lk(m);
      gripperCommandApplied = true;
      lk.unlock();
      cv.notify_one();
    }
  }
}

void SimulinkPandaGripper::waitForGripperCommand(){
  std::unique_lock<std::mutex> lk(m);
  cv.wait(lk, [&] { return gripperCommandApplied; });
  gripperCommandApplied = false;
}

double SimulinkPandaGripper::getGripperWidth(){
  return gripperState.width;
}
double SimulinkPandaGripper::getGripperMaxWidth(){
  return gripperState.max_width;
}
double SimulinkPandaGripper::getGripperIsGrasped(){
  return gripperState.is_grasped;
}
double SimulinkPandaGripper::getGripperGraspFailed(){
  return gripperGraspFailed;
}
double SimulinkPandaGripper::getGripperTemperature(){
  return gripperState.temperature;
}
int SimulinkPandaGripper::getGripperStateNewlyRead(){
  return stateNewlyReadCounter;
}
bool SimulinkPandaGripper::getTerminateGripperThread(){
  return terminateGripperThread;
}
int SimulinkPandaGripper::getGripperCurrentControlMode(){
  return gripperCurrentControlMode;
}

void SimulinkPandaGripper::updateGripperState(){
  gripperState = gripper->readOnce();
}

void SimulinkPandaGripper::performHoming(){
  gripper->homing();
}

void SimulinkPandaGripper::performGrasp(){
  if (!gripper->grasp(graspWidth, graspSpeed, graspForce, graspEpsilonInner,
                      graspEpsilonOuter)) {
    gripperGraspFailed = 1;
  } else {
    gripperGraspFailed = 0;
  }
}

void SimulinkPandaGripper::performMove(){
  gripper->move(moveWidth, moveSpeed);
}

void SimulinkPandaGripper::performStop(){
  gripper->stop();
}

void SimulinkPandaGripper::equalizeCommandCounter(){
    stateNewlyReadCounterPrev = stateNewlyReadCounter;
}

void SimulinkPandaGripper::updateCommandCounter(){
  stateNewlyReadCounter++;
}

bool SimulinkPandaGripper::gripperServerBusy(){
  return (stateNewlyReadCounterPrev = stateNewlyReadCounter);
}

void gripperControlThread_func(SimulinkPandaGripper& simulinkPandaGripper) {
  while (!simulinkPandaGripper.getTerminateGripperThread()) {
    simulinkPandaGripper.waitForGripperCommand();
    simulinkPandaGripper.equalizeCommandCounter();

    switch (simulinkPandaGripper.getGripperCurrentControlMode()) {
      case idle_:
        break;

      case read_state_:
        simulinkPandaGripper.updateGripperState();
        break;

      case homing_:
        simulinkPandaGripper.performHoming();
        break;

      case grasp_:
        simulinkPandaGripper.performGrasp();
        break;

      case move_:
        simulinkPandaGripper.performMove();
        break;

      case stop_:
        simulinkPandaGripper.performStop();
        break;
    }

    simulinkPandaGripper.updateCommandCounter();
  }
}