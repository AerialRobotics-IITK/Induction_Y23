#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/LaserScan.h>

void listenerCb(const sensor_msgs::LaserScan& msg){
	ROS_INFO("Range min [%f]", msg.range_min);
	// ROS_INFO("Division is %f", (msg.angle_max-msg.angle_min)/msg.angle_increment);
}

void listenerCb2(const std_msgs::String& msg){
	ROS_INFO("I heard: [%s]", msg.data.c_str());
}


int main(int argc, char** argv){
	ros::init(argc, argv, "listener");
	ros::NodeHandle nodeHandle;
	std::string topic;
	if(!nodeHandle.getParam("topic", topic)){
		ROS_WARN("Could not find topic parameter, defaulting to scan");
		topic = "scan";

	}
	else{
		ROS_INFO_STREAM("Read topic: " << topic);
//		ros::Subscriber sub = nodeHandle.subscribe(topic, 1, listenerCb);
	}
	int queue_size;
	if(!nodeHandle.getParam("queue_size", queue_size)){
		ROS_WARN("Could not find queue_size parameter, defaulting to 1");
		queue_size = 1;
	}
	else{
		ROS_INFO_STREAM("Read topic: " << queue_size);
//		ros::Subscriber sub = nodeHandle.subscribe(topic, 1, listenerCb);
	}
	ros::Subscriber sub = nodeHandle.subscribe(topic, queue_size, listenerCb);
	ros::spin();
}
