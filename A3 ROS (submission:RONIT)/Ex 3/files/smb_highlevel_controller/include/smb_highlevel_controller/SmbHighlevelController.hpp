#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>


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
	ros::Publisher velocity_publisher_;
	ros::Publisher marker_publisher_;
	std::string subscriberTopic_;
	int queueSize_;
	int xVelocity;
	int omegaZ;
	
	bool readParameters();
	void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg);
};

} /* namespace */
