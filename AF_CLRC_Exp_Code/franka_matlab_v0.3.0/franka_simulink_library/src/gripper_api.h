#ifndef GRIPPER_API_H
#define GRIPPER_API_H

#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <map>

#include <franka/gripper.h>

enum gripperControlModes  { idle_,
                            read_state_,
                            homing_,
                            grasp_,
                            move_,
                            stop_ };
                                
class SimulinkPandaGripper{
    
    std::string robotIP;
    std::unique_ptr<franka::Gripper> gripper;
    
    franka::GripperState gripperState;

    int stateNewlyReadCounter = 0;
    int stateNewlyReadCounterPrev = 0;
    int gripperGraspFailed = 0;

    double graspWidth = 0;
    double graspSpeed = 0;
    double graspForce = 0;
    double graspEpsilonInner = 0;
    double graspEpsilonOuter = 0;

    double moveWidth = 0;
    double moveSpeed = 0;

    int gripperCurrentControlMode = idle_;

    int triggerGripperCommand = 0;
    int triggerGripperCommandPrev = 0;

    bool terminateGripperThread = false;
    bool gripperCommandApplied = false;
    
    std::thread gripperControlThread;
    std::mutex m;
    std::condition_variable cv;
    
public:

    SimulinkPandaGripper(const char * robotIPMaskMask);
    ~SimulinkPandaGripper();
    
    bool gripperControlRequested();
    void parseGripperCommand(double *gripperCommandVector);
    void applyGripperCommand();
    void waitForGripperCommand();
    
    double getGripperWidth();
    double getGripperMaxWidth();
    double getGripperIsGrasped();
    double getGripperGraspFailed();
    double getGripperTemperature();
    int getGripperStateNewlyRead();
    bool getTerminateGripperThread();
    int getGripperCurrentControlMode();
    
    void updateGripperState();
    void performHoming();
    void performGrasp();
    void performMove();
    void performStop();
    void equalizeCommandCounter();
    void updateCommandCounter();

    bool gripperServerBusy();
    
};

extern void gripperControlThread_func(SimulinkPandaGripper& simulinkPandaGripper);

#endif