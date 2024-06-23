// This source file provides all the functionalities of the Smb2HighlevelController class...

#include "smb2_highlevel_controller/smb2_highlevel_controller.hpp"

namespace smb2_highlevel_controller{



// Constructor definition 
  Smb2HighlevelController::Smb2HighlevelController(ros::NodeHandle& nh1):scan_sub_nh(nh1){};



// call_back_func definition
  void Smb2HighlevelController::call_back_func(const sensor_msgs::LaserScan& in_msg){
    //modify ros::Rate rate here
    static ros::Rate rate(10);
    const static int number_of_measurements = 360;
    const static float delta_angle = 0.008700000122189522;
    const static float start_angle = -1.5707999467849731;
    static ros::NodeHandle temp_pub_nh;
    static geometry_msgs::Twist msg;
    // modify queue_size here
    static ros::Publisher temp_pub = temp_pub_nh.advertise<geometry_msgs::Twist>("cmd_vel",10);
    
    static float min_range = in_msg.ranges[0];
    static int min_index = 0;
    
    for(int i=0;i<number_of_measurements;i++){
        if(in_msg.ranges[i]<min_range){
        min_range = in_msg.ranges[i];
        min_index = i;
        }        
    } 
    
    /////////////////////////////////////////////////////////            temp stuff
    //////                                                                temp_msg
    //static std_msgs::Int32 temp_msg;
    //static ros::NodeHandle temp_nh;
    //static ros::Publisher temp = temp_nh.advertise<std_msgs::Int32>("temp_topic",10);
    
    //temp_msg.data = min_index;
    
    ////////////////////////////////////////////////////////
    
    
    // message modification
    if(min_range < 0.5 && min_index>170 && min_index<190){
      //smb has reached the cylinder
      msg.linear.x = 0.0;
      msg.angular.z = 0.0; 
    }
    else if(min_index>=155 && min_index<=205){
      //set z rotation message to zero
      msg.linear.x = 2.0 * (min_range / 20.0); 
      //set forward (x) message
      msg.angular.z = 0.0;
    }
    else{
      //set forward(x) message to zero
      msg.linear.x = 0.0;
      // set z rotation message
      msg.angular.z = (min_index-180.0)/80.0;
    }
    
    temp_pub.publish(msg);
    
    //temp.publish(temp_msg);
    
    ros::spinOnce();
    rate.sleep();
  }


// start_scan_subscriber definition
  void Smb2HighlevelController::start_controller(){
  	
    ros::NodeHandle nh("~");
    std::string topic_name;
    int queue_size;
    
    nh.getParam("topic_name",topic_name);
    nh.getParam("queue_size",queue_size);
    
    ros::Subscriber scan_subscriber = scan_sub_nh.subscribe(topic_name,queue_size,call_back_func);
    
    ros::spin();
  }
}
