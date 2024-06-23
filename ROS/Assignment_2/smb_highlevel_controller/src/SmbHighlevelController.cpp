#include <smb_highlevel_controller/SmbHighlevelController.hpp>

namespace smb_highlevel_controller
{

  SmbHighlevelController::SmbHighlevelController(ros::NodeHandle &nodeHandle) : nodeHandle_(nodeHandle)
  {
    if (!Parameters())
    {
      ros::requestShutdown();
    }
    subscriber = nodeHandle_.subscribe(Topic,Size,&SmbHighlevelController::scanCallback,this);
    ROS_INFO("Successfully launched node.");
  }

  SmbHighlevelController::~SmbHighlevelController()
  {
  }
  bool SmbHighlevelController::Parameters()
  {
    if (!(nodeHandle_.getParam("Topic", Topic) &&
          nodeHandle_.getParam("queueSize", Size)))
    {
      return false;
    }
    return true;
  }
  void SmbHighlevelController::scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
  {
    auto min= *std::min_element(msg->ranges.begin(), msg->ranges.end());
    ROS_INFO_STREAM("Smallest distance measurement :"<< min << std::endl ); 
  }


} /* namespace */