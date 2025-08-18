# Filtered Regressor Simulation

This repository contains simulation and test code for filtered regression algorithms.

## Dependencies

- [ROS](https://www.ros.org/)
- [Eigen](https://eigen.tuxfamily.org/)

## Usage

To start the simulation, run:

```bash
roslaunch filter_regressor sim.launch use_analytic:=1 # use analytic regressor

roslaunch filter_regressor sim.launch use_analytic:=0 # use pinocchio regressor
```

## Description

This project provides a simulation environment for testing and validating filtered regression methods using ROS and Eigen.
