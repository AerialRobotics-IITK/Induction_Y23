#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

class PillarDetector
{
public:
    PillarDetector()
    {
        // Initialize the subscriber and publisher
        scan_sub_ = nh_.subscribe("/scan", 1, &PillarDetector::scanCallback, this);
        cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

        // Set initial linear and angular speeds
        linear_speed_ = 0.5;
        angular_speed_ = 1.0;
    }

    void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
    {
        // Extract position of the pillar from the laser scan data
        auto ranges = msg->ranges;
        auto min_distance = *std::min_element(ranges.begin(), ranges.end());
        auto min_index = std::distance(ranges.begin(), std::min_element(ranges.begin(), ranges.end()));
        auto angle = msg->angle_min + min_index * msg->angle_increment;

        // Log the position
        ROS_INFO("Pillar detected at angle: %f, distance: %f", angle, min_distance);

        // Create and publish a twist message to move towards the pillar
        geometry_msgs::Twist twist;
        twist.linear.x = linear_speed_;
        twist.angular.z = -angle * angular_speed_;
        cmd_vel_pub_.publish(twist);
    }

private:
    ros::NodeHandle nh_;
    ros::Subscriber scan_sub_;
    ros::Publisher cmd_vel_pub_;
    double linear_speed_;
    double angular_speed_;
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pillar_detector");
    PillarDetector pd;
    ros::spin();
    return 0;
}
