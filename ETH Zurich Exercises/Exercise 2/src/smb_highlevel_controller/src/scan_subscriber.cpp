#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

void call_back_func(const sensor_msgs::LaserScan& msg){
    
    
    float min = msg.ranges[0];
    
    int size = sizeof(msg.ranges)/sizeof(msg.ranges[0]);
    
    for(int i=0;i<size;i++){
        if(msg.ranges[i]<min){
            min=msg.ranges[i];
        }
    
    std::string disp_msg = "Smallest Distance is " + std::to_string(min);    
    
    ROS_INFO_STREAM(disp_msg);

    
}
}

int main(int argc, char* argv[]){

    ros::init(argc,argv,"scan_subscriber");
    ros::NodeHandle nh;
    
    // remember to take topic name and queue size from parameter file parameter.yaml
    
    ros::NodeHandle nh2("~");
    std::string topic_name;
    int queue_size;
    
    
    nh2.getParam("topic_name",topic_name);
    nh2.getParam("queue_size",queue_size);
    
    
    ros::Subscriber scan_subscriber = nh.subscribe(topic_name, queue_size, call_back_func);
    
    ros::spin();
    
    return 0;

}

