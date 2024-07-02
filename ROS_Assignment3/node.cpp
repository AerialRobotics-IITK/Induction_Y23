#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

class robo{
    private:
        ros::NodeHandle nh;
        ros::Subsciber subscriber;
        ros::Publisher publisher;
    public:
        robo(ros::NodeHandle& nodeHandle) :nh(nodeHandle){
            subscriber = nh.subscribe("/scan",10,ScanCallBack);  //subscribes to scan topic
            publisher = nh.advertise <geometry_msgs::Twist>("/cmd_vel", 10);
        }
        void ScanCallBack(const sensor_msgs::LaserScan::ConstPtr& msg);
}

void robo::ScanCallBack(const sensor_msgs::LaserScan::ConstPtr& msg){
    ROS_INFO("Current Linear Speed: %f", msg.linear.x);
    ROS_INFO("Current Angular Speed: %f", msg.angular.z);

    auto closest = std::min_element(msg->ranges.begin(), msg->ranges.end());
    auto closest_index = std::distance(msg->ranges.begin(), closest);   //Find index of angle of pillar
    const auto angle = msg->angle_min + msg->angle_increment * closest_index;  //Angular position of pillar
    

    const auto correction = angle;  //error = 0.00 - angle
    float omega_z = 0.1;
    float linear_velocity=1.0;       

    geometry_msgs::Twist velocity;
    
    //P controller where the commanded angular velocity is proportional to the error in angle 
    velocity.angular.z = (omega_z * correction); 
    velocity.linear.x = 1.0;   

    //Stop if an obstacle is too close
    if (min_range < 1.0) {
        velocity.linear.x = 0.0;
        velocity.angular.z = 0.0;
    }
    publisher.publish(velocity);
};


int main(int argc, char* argv[]){
    ros::init(argc, argv, "talker"); 
    ros::NodeHandle nh;
    robo Robo(nh);
    ros::spin();
    return 0;
}