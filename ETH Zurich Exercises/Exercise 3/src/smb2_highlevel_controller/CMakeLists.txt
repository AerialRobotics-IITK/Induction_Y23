cmake_minimum_required(VERSION 3.0.2)
project(smb2_highlevel_controller)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  sensor_msgs
  geometry_msgs
  std_msgs
)


generate_messages(
  DEPENDENCIES
  sensor_msgs
  geometry_msgs
  std_msgs
)

#catkin configuration
catkin_package(
  INCLUDE_DIRS
  include #add the header .hpp file in include directory with the class and member functions implemented
  CATKIN_DEPENDS
  message_runtime
  roscpp
  sensor_msgs
  geometry_msgs
  std_msgs
)

#build

#################
############ read about this shit in ros wiki
###################
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

#############################
####################  add the source code for this to launch the node
###########################  also write a launch file
add_executable(${PROJECT_NAME}_node src/${PROJECT_NAME}_node.cpp src/${PROJECT_NAME}.cpp)
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES})

####### 
#### do something about the things under the install section in other CMakeLists.txt files


