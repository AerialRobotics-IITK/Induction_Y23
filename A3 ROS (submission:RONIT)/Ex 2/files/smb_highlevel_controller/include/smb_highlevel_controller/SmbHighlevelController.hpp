#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

// #include <sensor_msgs/scan>
namespace smb_highlevel_controller {

/*!
 * Class containing the Husky Highlevel Controller
 */
class SmbHighlevelController {
public:
	/*!
	 * Constructor.
	 */
	SmbHighlevelController(ros::NodeHandle& nodeHandle);

	/*!
	 * Destructor.
	 */
	virtual ~SmbHighlevelController();

private:
	ros::NodeHandle nodeHandle_;
	ros::Subscriber subscriber_;
	std::string subscriberTopic_;
	int queueSize_;
	
	bool readParameters();
	void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg);
};

} /* namespace */
