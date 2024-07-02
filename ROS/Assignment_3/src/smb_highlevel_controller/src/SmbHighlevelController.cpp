#include <ros/ros.h>
#include <smb_highlevel_controller/SmbHighlevelController.hpp>
#include <sensor_msgs/LaserScan.h>

namespace smb_highlevel_controller {

void laserscan_callback(const sensor_msgs::LaserScan& scan_msg){
	ROS_INFO("Closest distance among the measures: %f", scan_msg.range_min);
}

SmbHighlevelController::SmbHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{
	ROS_INFO("Node created");
	ros::Subscriber sub = nodeHandle.subscribe("scan", 1, laserscan_callback);
}

SmbHighlevelController::~SmbHighlevelController()
{
}

} /* namespace */
