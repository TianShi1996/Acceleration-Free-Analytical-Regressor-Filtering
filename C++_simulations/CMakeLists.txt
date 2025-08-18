cmake_minimum_required(VERSION 3.0.2)
project(filtered_regressor)
set(eigenpy_DIR "/opt/openrobots/lib/cmake/eigenpy")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
find_package(pinocchio 2.6.9 REQUIRED)



###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
        INCLUDE_DIRS
        include

        LIBRARIES
        ${PROJECT_LIBRARIES}

        CATKIN_DEPENDS
        geometry_msgs
        image_geometry
        roscpp
        sensor_msgs
        std_msgs
)
add_definitions(-DBASE_PWD="${CMAKE_CURRENT_SOURCE_DIR}")


aux_source_directory(src/models SRC_models)


include_directories(
        include
        ${catkin_INCLUDE_DIRS}
)

add_executable(sim_regressor src/sim_regressor.cpp ${SRC_models})
target_link_libraries(sim_regressor
  ${catkin_LIBRARIES}
  pinocchio::pinocchio
)
