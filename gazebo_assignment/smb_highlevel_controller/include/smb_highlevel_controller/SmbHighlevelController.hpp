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
	ros::NodeHandle nodeHandle_;
        ros::Subscriber subscriber_; // Declare subscriber_ as a member variable

    void laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& msg);
};

} /* namespace */
