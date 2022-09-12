cmake_minimum_required(VERSION 3.23)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(untitled main.cpp Pose3d.cpp Pose3d.h MathUtils.cpp MathUtils.h RobotArm.cpp RobotArm.h)
target_link_libraries (untitled Eigen3::Eigen)
