//  Copyright (c) 2020 Franka Emika GmbH - All Rights Reserved
//  This file is subject to the terms and conditions defined in the file
//  'LICENSE' , which is part of this package

#ifndef CONTROL_MODES_UTILS_H
#define CONTROL_MODES_UTILS_H

#include <string.h>

#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <franka/exception.h>
#include <franka/robot.h>

template<typename T>
T handlingParseInfo(SimulinkPandaRobot& simulinkPandaRobot);

template<>
franka::Torques handlingParseInfo<franka::Torques>(SimulinkPandaRobot& simulinkPandaRobot){
    return simulinkPandaRobot.getControllerInputTorques();
}

template<>
franka::JointPositions handlingParseInfo<franka::JointPositions>(SimulinkPandaRobot& simulinkPandaRobot){
    return simulinkPandaRobot.getControllerInputJointPositions();
}

template<>
franka::JointVelocities handlingParseInfo<franka::JointVelocities>(SimulinkPandaRobot& simulinkPandaRobot){
    return simulinkPandaRobot.getControllerInputJointVelocities();
}

template<>
franka::CartesianPose handlingParseInfo<franka::CartesianPose>(SimulinkPandaRobot& simulinkPandaRobot){
    if (simulinkPandaRobot.getElbowControl()){
        return {simulinkPandaRobot.getControllerInputCartesianPose(), simulinkPandaRobot.getControllerInputElbowPosition()};
    }else{
        return simulinkPandaRobot.getControllerInputCartesianPose();
    }
}

template<>
franka::CartesianVelocities handlingParseInfo<franka::CartesianVelocities>(SimulinkPandaRobot& simulinkPandaRobot){
    if (simulinkPandaRobot.getElbowControl()){
        return {simulinkPandaRobot.getControllerInputCartesianVelocities(), simulinkPandaRobot.getControllerInputElbowPosition()};
    }else{
        return simulinkPandaRobot.getControllerInputCartesianVelocities();
    }
}

template<typename T>
constexpr long unsigned int secondaryCallbackInputWidth();

template<>
constexpr long unsigned int secondaryCallbackInputWidth<franka::JointPositions>(){
    return 7;
}

template<>
constexpr long unsigned int secondaryCallbackInputWidth<franka::JointVelocities>(){
    return  7;
}

template<>
constexpr long unsigned int secondaryCallbackInputWidth<franka::CartesianPose>(){
    return 16;
}

template<>
constexpr long unsigned int secondaryCallbackInputWidth<franka::CartesianVelocities>(){
    return 6;
}

#endif