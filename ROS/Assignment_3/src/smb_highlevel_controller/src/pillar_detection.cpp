#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <limits>

class PillarController {
private:
    ros::Subscriber scan_subscriber_;
    ros::Publisher cmd_vel_publisher_;

    // Proportional gain for angular velocity
    float Kp_ = 20.0;

    void CallBack(const sensor_msgs::LaserScan& in_msg) {
        // Initialize min_range to a large value
        float min_range = std::numeric_limits<float>::infinity();
        int min_index = 0;

        // Iterate over the ranges to find the minimum valid range and its index
        for (size_t i = 0; i < in_msg.ranges.size(); ++i) {
            float range = in_msg.ranges[i];
            if (std::isfinite(range) && range < min_range) {
                min_range = range;
                min_index = i;
            }
        }

        // Calculate the angle of the closest point
        float angle = in_msg.angle_min + min_index * in_msg.angle_increment;

        // Create and populate the Twist message
        geometry_msgs::Twist msg;
        msg.linear.x = 1.0;  
        msg.angular.z = Kp_ * angle;  

        // Stop if an obstacle is too close
        if (min_range < 1.0) {
            msg.linear.x = 0.0;
            msg.angular.z = 0.0;
        }
        // Printing current linear and angular speed.
        ROS_INFO("Current Linear Speed: %f", msg.linear.x);
        ROS_INFO("Current Angular Speed: %f", msg.angular.z);
        // Publish the command
        cmd_vel_publisher_.publish(msg);
    }

public:
    PillarController() {
        ros::NodeHandle nh;

        // Initialize subscriber and publisher
        scan_subscriber_ = nh.subscribe("/scan", 10, &PillarController::CallBack, this);
        cmd_vel_publisher_ = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "pillar_controller_node");
    PillarController controller;
    ros::spin();
    return 0;
}
