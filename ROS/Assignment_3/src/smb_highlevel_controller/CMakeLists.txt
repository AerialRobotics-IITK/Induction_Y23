cmake_minimum_required(VERSION 3.0.2)
project(smb_highlevel_controller)

# Use C++11
add_compile_options(-std=c++11)

# Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  geometry_msgs
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp sensor_msgs geometry_msgs
)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

# Declare a C++ executable
add_executable(smb_highlevel_controller_node
  src/smb_highlevel_controller_node.cpp
  src/SmbHighlevelController.cpp
)
add_executable(pillar_detector src/pillar_detection.cpp)
# Specify libraries to link a library or executable target against
target_link_libraries(smb_highlevel_controller_node
  ${catkin_LIBRARIES}
)

target_link_libraries(pillar_detector
  ${catkin_LIBRARIES}
)

#############
## Install ##
#############

# Mark executables for installation
install(TARGETS smb_highlevel_controller_node
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
