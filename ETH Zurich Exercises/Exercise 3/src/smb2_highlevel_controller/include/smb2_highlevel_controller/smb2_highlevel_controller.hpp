// This header file defines the prototypes/barebones of the Smb2HighlevelController class 

#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int32.h>

namespace smb2_highlevel_controller{

  class Smb2HighlevelController{  
  
    private:
    	ros::NodeHandle scan_sub_nh;//1
 
    public:
    	Smb2HighlevelController(ros::NodeHandle& nh1);//1  	 
    	static void call_back_func(const sensor_msgs::LaserScan& msg);//2
    	void start_controller();//3
    	
  };
}
