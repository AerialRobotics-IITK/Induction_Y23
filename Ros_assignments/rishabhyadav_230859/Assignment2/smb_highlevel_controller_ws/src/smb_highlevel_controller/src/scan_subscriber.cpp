#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {
    
    float min_distance = std::numeric_limits<float>::infinity();
    for (float range : msg->ranges) {
        if (range < min_distance) {
            min_distance = range;
        }
    }
    ROS_INFO("Smallest distance is: %.2f", min_distance);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "scan_subscriber");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/scan", 1000, scanCallback);

    ros::spin();

    return 0;
}
