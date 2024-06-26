#include<ros/ros.h>
#include<sensor_msgs/LaserScan.h>

void callbackScan(const sensor_msgs::LaserScan::ConstPtr& scan_data){
    float min_distance = *std::min_element(scan_data->ranges.begin(),scan_data->ranges.end());

    ROS_INFO("Smallest distance: %.2f meters",min_distance);
}

int main(int argc, char** argv){
    ros::init(argc, argv, "smb_highlevel_controller");
    ros::NodeHandle nh;
    std::string scan_topic;
    int queue_size;

    nh.param<std::string>("scan_topic",scan_topic, "/scan");
    nh.param<int>("queue_size",queue_size,10);
    ros::Subscriber subscriber = nh.subscribe(scan_topic,queue_size, callbackScan);
    ros::spin();
    return 0;
}
