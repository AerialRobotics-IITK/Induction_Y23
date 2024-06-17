#include <smb_highlevel_controller/SmbHighlevelController.hpp>
#include <algorithm>

namespace smb_highlevel_controller {

SmbHighlevelController::SmbHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{
  // Load parameters from the parameter server
  std::string scan_topic, pointcloud_topic;
  int queue_size;

  nodeHandle_.param<std::string>("scan_topic", scan_topic, "/scan");
  nodeHandle_.param<int>("queue_size", queue_size, 10);
  nodeHandle_.param<std::string>("pointcloud_topic", pointcloud_topic, "/point_cloud");

  // Initialize subscribers
  scanSubscriber_ = nodeHandle_.subscribe(scan_topic, queue_size, &SmbHighlevelController::scanCallback, this);
  pointCloudSubscriber_ = nodeHandle_.subscribe(pointcloud_topic, queue_size, &SmbHighlevelController::pointCloudCallback, this);
}

SmbHighlevelController::~SmbHighlevelController()
{
}

void SmbHighlevelController::scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  if (!msg->ranges.empty()) {
    float min_distance = *std::min_element(msg->ranges.begin(), msg->ranges.end());
    ROS_INFO_STREAM("Minimum distance: " << min_distance);
  } else {
    ROS_WARN("Received an empty laser scan message.");
  }
}

void SmbHighlevelController::pointCloudCallback(const sensor_msgs::PointCloud2::ConstPtr& msg)
{
  int num_points = msg->width * msg->height;
  ROS_INFO_STREAM("Number of points in point cloud: " << num_points);
}

} /* namespace */

