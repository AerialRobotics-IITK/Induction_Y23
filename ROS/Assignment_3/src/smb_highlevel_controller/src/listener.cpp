#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>

void listenerCb(const sensor_msgs::LaserScan& msg){
  float pq = msg.ranges[0];
  for (auto i = msg.ranges.begin(); i != msg.ranges.end(); i++) {
    if(*i < pq)  {
      pq = *i;
    }
  }
	// ROS_INFO("Division is %f", (msg.angle_max-msg.angle_min)/msg.angle_increment);
	ROS_INFO("Range min [%f]", pq);
}

void listenerCb2(const std_msgs::String& msg){
	ROS_INFO("I heard: [%s]", msg.data.c_str());
}

void pillar_controller_cb(const sensor_msgs::LaserScan& scan_msg){
    static ros::Rate rate(10);
    static ros::NodeHandle nh;
    static geometry_msgs::Twist msg;
    static ros::Publisher pb = nh.advertise<geometry_msgs::Twist>("cmd_vel",10);
	const double min_ang = 0.02;
	const int range_threshold = 20;
    float min_range = scan_msg.ranges[0];
    int min_index = 0;
	// static switched_sides = false;
    for(int i=0;i<scan_msg.ranges.size();i++){		
        if(scan_msg.ranges[i]<min_range){
        min_range = scan_msg.ranges[i];
        min_index = i;
        }        
    }

	if(min_range == std::numeric_limits<float>::infinity()){
		// ROS_INFO("Size is not %d", scan_msg.ranges.size());
		msg.linear.x=0.0;
		msg.angular.z = 0.3;
	}
	else{
		if((min_index-scan_msg.ranges.size()/2) < range_threshold || (min_index-scan_msg.ranges.size()/2) > 0-range_threshold){
			msg.linear.x=1.0;
			msg.angular.z = (min_index*1.0-scan_msg.ranges.size()*0.5)/100.0;
		}
		else{
			if(min_range > 2.0){
				msg.linear.x = 0.0;
			}
		if(min_index-scan_msg.ranges.size()*0.5 > 0){
			// ROS_INFO("Size is definitely %d", scan_msg.ranges.size());
			msg.angular.z = std::max((min_index*1.0-scan_msg.ranges.size()*0.5)/40.0, min_ang);
		}
		else{
			// ROS_INFO("On the other side now");
			msg.angular.z = std::min((min_index*1.0-scan_msg.ranges.size()*0.5)/40.0, -min_ang);
		}
		}
	}
	// msg.linear.x=0.0;
	// ROS_INFO("Setting angular z to be %f", ((min_index*1.0-scan_msg.ranges.size()*1.0)));
	// msg.angular.z=(min_index*1.0-scan_msg.ranges.size()*1.0)/40.0;
    pb.publish(msg);
    ros::spinOnce();
    rate.sleep();
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
	ros::Subscriber sub = nodeHandle.subscribe(topic, queue_size, pillar_controller_cb);
	ros::spin();
}
