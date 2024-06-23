// This source file just initiates the smb2_highlevel_controller_node and loads the parameters from the config.yaml file

#include <ros/ros.h>
#include "smb2_highlevel_controller/smb2_highlevel_controller.hpp"

int main(int argc, char* argv[]){
  
  ros::init(argc,argv,"smb2_highlevel_controller_node");
  ros::NodeHandle nodeHandle_1;
  
  smb2_highlevel_controller::Smb2HighlevelController Controller(nodeHandle_1);
  
  Controller.start_controller();
  
  return 0;
}

