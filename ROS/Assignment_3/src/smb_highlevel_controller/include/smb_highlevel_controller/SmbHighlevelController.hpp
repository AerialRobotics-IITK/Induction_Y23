#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

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
	bool Parameters();
	ros::NodeHandle nodeHandle_;
	ros::Subscriber subscriber;
	std::string Topic;
	int Size ;
	void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg);
	
};

} /* namespace */
