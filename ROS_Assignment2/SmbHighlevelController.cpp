#include <smb_highlevel_controller/SmbHighlevelController.hpp>

namespace smb_highlevel_controller{

SmbHighlevelController::SmbHighlevelController(ros::NodeHandle& nodeHandle) :nodeHandle_(nodeHandle)
{
    nodeHandle_.getParam("topic_name", topic_name);
    nodeHandle_.getParam("queue_size",queue_size);
    subscriber = nodeHandle_.subscribe(topic_name, queue_size,ScanCallBack);
    ROS_INFO_STREAM("\nNode subscribed to" << topic_name << "\n" << std::endl); 
}

void SmbHighlevelController::ScanCallBack(const sensor_msgs::LaserScan::ConstPtr& msg){
    auto min = * std::min_element(msg->ranges.begin(), msg->ranges.end());
    ROS_INFO_STREAM("Smallest distance measurement: " << min << std::endl); 
}

}