#include <smb_highlevel_controller/SmbHighlevelController.hpp>

namespace smb_highlevel_controller {

SmbHighlevelController::SmbHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{
  if (!readParameters()) {
    ROS_ERROR("Could not read parameters.");
    ros::requestShutdown();
  }
  
  subscriber_ = nodeHandle_.subscribe(subscriberTopic_, queueSize_,
                                      &SmbHighlevelController::scanCallback, this);
                                      
  // Creating a publisher on the topic /cmd_vel to send a twist command to SMB
  velocity_publisher_ = nodeHandle_.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
  
  // Creating a publisher on the topic /visualization_marker display a marker in Rviz
  marker_publisher_ = nodeHandle_.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
  
  ROS_INFO("Successfully launched node.");
}


SmbHighlevelController::~SmbHighlevelController()
{
}

bool SmbHighlevelController::readParameters()
{
  if (!(nodeHandle_.getParam("subscriber_topic", subscriberTopic_) &&
        nodeHandle_.getParam("queue_size", queueSize_)&&
        nodeHandle_.getParam("x_velocity", xVelocity)&&
        nodeHandle_.getParam("omega_z", omegaZ))) {
    return false;
  }
  return true;
}

void SmbHighlevelController::scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  auto min= std::min_element(msg->ranges.begin(), msg->ranges.end());
  
  // Extracting Pillar Position w.r.t Robot
  auto min_distance_index = std::distance(msg->ranges.begin(), min); 
  const auto min_distance = *min;
  const auto angle= msg->angle_min + msg->angle_increment * min_distance_index; // angle from x-axis
  
  auto pillar_x_coordinate = min_distance * cos(angle);
  auto pillar_y_coordinate = min_distance * sin(angle);
  
  ROS_INFO_STREAM("\nClosest distance:" << min_distance << "; Pillar(x,y,θ): (" << 
  pillar_x_coordinate << "," <<pillar_y_coordinate << "," << angle << std::endl );
  
  
  // Proportional controller that drives the robot 
  const auto target_angle = 0.00;
  const auto error = target_angle - angle;
  geometry_msgs::Twist velocity;
  
  velocity.angular.z = -(omegaZ * error); // angular velocity is proportional to the error in angle
  if ((min_distance < std::numeric_limits<double>::infinity()) && (min_distance > 0.9)){
  	velocity.linear.x = xVelocity;
  }
  else {
  	velocity.linear.x = 0;
  }
  
  velocity_publisher_.publish(velocity);
  
 // Publishing a visualization marker for RViz that shows the estimated position of the pillar.
 visualization_msgs::Marker marker;
 marker.header.frame_id = "rslidar"; // try base_link
 marker.header.stamp = ros::Time();
 marker.ns = "smb_highlevel_controller";
 marker.id = 0;
 marker.type = visualization_msgs::Marker::SPHERE;
 marker.action = visualization_msgs::Marker::ADD; 
 marker.pose.position.x = pillar_x_coordinate;
 marker.pose.position.y = pillar_y_coordinate;
 marker.pose.position.z = 0;
 marker.pose.orientation.x = 0.0;
 marker.pose.orientation.y = 0.0;
 marker.pose.orientation.z = 0.0;
 marker.pose.orientation.w = 1.0;
 marker.scale.x = 0.5;
 marker.scale.y = 0.5;
 marker.scale.z = 0.5;
 marker.color.a = 1.0;
 marker.color.r = 0.0;
 marker.color.g = 1.0;
 marker.color.b = 0.0;
 marker_publisher_.publish( marker );

}


} /* namespace */
