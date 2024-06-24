#include <ros/ros.h>
#include "smb_highlevel_controller/SmbHighlevelController.hpp"

int main(int argc, char** argv) {
  ros::init(argc, argv, "smb_highlevel_controller");
  ros::NodeHandle nodeHandle("~");
  
  while (1){
	  std::string ans;
	  ROS_INFO_STREAM("Enter 'start' to start the Simulation: ");
	  std::cin >> ans;
	  if (ans=="start") break;
	  else continue;
  }
  
  smb_highlevel_controller::SmbHighlevelController smbHighlevelController(nodeHandle);

  ros::spin();
  return 0;
}
