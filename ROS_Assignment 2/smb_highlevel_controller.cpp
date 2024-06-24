#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/PointCloud2.h>
#include <algorithm>
#include <limits>


void laserScanCallback(const sensor_msgs::LaserScan& msg){
    if (!msg.ranges.empty()) {
        float min_distance = *std::min_element(msg.ranges.begin(), msg.ranges.end());
        ROS_INFO("smallest distance: [%f]", min_distance);
    } else {
        ROS_WARN("warning: empty msg");
    }
}



int main(int argc, char** argv)
{
    ros::init(argc, argv, "listener");
    ros::NodeHandle nh;
    std::string laser_topic_name;
    int laser_queue_size;
    nh.param<std::string>("scan_subscriber/topic_name", laser_topic_name, "/scan");
    nh.param<int>("scan_subscriber/queue_size", laser_queue_size, 1);


    ros::Subscriber laser_sub = nh.subscribe(laser_topic_name, laser_queue_size, laserScanCallback);
    ros::spin();
    return 0;
}
