#include <smb_highlevel_controller/SmbHighlevelController.hpp>

namespace smb_highlevel_controller {

SmbHighlevelController::SmbHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{   
    //load values from param file, or else use default values
    std::string topic_name;
    int queue_size;
    nodeHandle_.param<std::string>("scan_topic", topic_name, "/scan");
    nodeHandle_.param<int>("queue_size", queue_size, 10);
    // create a subscriber
    subscriber_ = nodeHandle_.subscribe(topic_name, queue_size, &SmbHighlevelController::laserScanCallback, this);
}

SmbHighlevelController::~SmbHighlevelController()
{
}

void SmbHighlevelController::laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {
    // Ensure there are ranges in the message
    if (msg->ranges.empty()) {
        ROS_WARN("Laser scan message has no data.");
        return;
    }
    
    ROS_INFO("NODE RUNNING!");
    // Find the smallest distance in the ranges array
    float minDistance = std::numeric_limits<float>::infinity();
    for (float range : msg->ranges) {
        if (range < minDistance) {
            minDistance = range;
        }
    }

    // Output the smallest distance to the terminal
    ROS_INFO("Smallest distance: %.2f meters", minDistance);
}

} /* namespace */
