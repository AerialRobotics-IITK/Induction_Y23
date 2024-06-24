#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <cmath>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>
#include "smb_highlevel_controller/SmbHighlevelController.hpp"

class Handler {
public:
    Handler() : nodeHandle("~"), publisher(), vis_pub(),subscriber(), smbHighlevelController(nodeHandle) {
        nodeHandle.param("scan_topic", scan_topic, std::string("/scan"));
        nodeHandle.param("queue_size", queue_size, 100);
        subscriber = nodeHandle.subscribe(scan_topic, queue_size, &Handler::scanCallback, this);
        publisher = nodeHandle.advertise<geometry_msgs::Twist>("/cmd_vel", queue_size);
        vis_pub = nodeHandle.advertise<visualization_msgs::Marker>( "/visualization_marker",100 );

        nodeHandle.getParam("/Kp_angular", Kp_angular);
        nodeHandle.getParam("/Kp_linear", Kp_linear);
    }
void Marker1(double x, double y){
    visualization_msgs::Marker marker;
    marker.header.frame_id = "base_link";
    marker.header.stamp = ros::Time();
    marker.ns = "my_namespace";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::SPHERE;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = x;
    marker.pose.position.y = y;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;
    marker.color.a = 1.0; // Don't forget to set the alpha!
    marker.color.r = 0.0;
    marker.color.g = 1.0;
    marker.color.b = 0.0;
    vis_pub.publish( marker );
}
    void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {
        std::vector<float> ranges = msg->ranges;
        float angle_increment = msg->angle_increment;
        float angle_min = msg->angle_min;
        float min_distance = ranges[0];
        float ray_angle = angle_min;

        for (size_t i = 1; i < ranges.size(); ++i) {
            if (ranges[i] < min_distance) {
                min_distance = ranges[i];
                ray_angle = angle_min + (i * angle_increment);
            }
        }

        double linear_velocity = Kp_linear * min_distance;
        double angular_velocity = Kp_angular * ray_angle*10;
        double angle_rad=ray_angle;
        double x=min_distance*cos(angle_rad);
        double y=min_distance*sin(angle_rad);

        geometry_msgs::Twist cmd_vel;
        cmd_vel.linear.x = linear_velocity;
        cmd_vel.angular.z = angular_velocity;
        publisher.publish(cmd_vel);

        ROS_INFO("Smallest distance: %f", min_distance);
        ROS_INFO("angle: %f", ray_angle);
        Marker1(x,y);
        
    }
    
private:
    ros::NodeHandle nodeHandle;
    ros::Publisher publisher;
    ros::Publisher vis_pub;
    ros::Subscriber subscriber;
    std::string scan_topic;
    int queue_size;
    double Kp_linear;
    double Kp_angular;
    smb_highlevel_controller::SmbHighlevelController smbHighlevelController;
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "smb_highlevel_controller");
    Handler hd;
    ros::spin();
    return 0;
}

