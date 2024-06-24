cmake_minimum_required(VERSION 3.0.2)
project(my_package)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  gazebo_ros
  pointcloud_to_laserscan
  rviz
  smb_control
  smb_gazebo
  # smb_description
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

## Declare a catkin package
catkin_package()

## Specify additional locations of header files
## Your package locations should be included here
include_directories(
  ${catkin_INCLUDE_DIRS}
  # Add any additional include directories here if needed
)

## Declare a C++ executable
add_executable(smb_highlevel_controller src/smb_highlevel_controller.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(smb_highlevel_controller
  ${catkin_LIBRARIES}
  # Add any additional libraries here if needed (e.g., PCL libraries)
)

## Add dependencies to the executable
add_dependencies(smb_highlevel_controller ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

