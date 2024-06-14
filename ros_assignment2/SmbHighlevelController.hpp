#ifndef SMB_HIGHLEVEL_CONTROLLER_HPP
#define SMB_HIGHLEVEL_CONTROLLER_HPP

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/PointCloud2.h>

namespace smb_highlevel_controller {

class SmbHighlevelController
{
public:
  SmbHighlevelController(ros::NodeHandle& nodeHandle);
  virtual ~SmbHighlevelController();

private:
  void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg);
  void pointCloudCallback(const sensor_msgs::PointCloud2::ConstPtr& msg);

  ros::NodeHandle& nodeHandle_;
  ros::Subscriber scanSubscriber_;
  ros::Subscriber pointCloudSubscriber_;
};

} /* namespace */

#endif /* SMB_HIGHLEVEL_CONTROLLER_HPP */

