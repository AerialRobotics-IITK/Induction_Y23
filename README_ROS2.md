# Here are the steps to follow to complete the assignment 2
(Make sure you are using Ubuntu 20.04 version before following these steps.-)
1) Download the smb_highlevel_controller.zip file from the course website, unzip it and place it in the git folder made in assignment 1.
2) Open a terminal ans source the ros setup using 
```bash
source /opt/ros/noetic/setup.bash
```
Navigate to ~/Workspaces/smb_ws/src/ and make a symlink to the file
```bash
ln -s ~/git/smb_highlevel_controller/
```
3) Then, inspect the CMakelists.txt and package.xml files in the dowloaded package.
4) To create a subscriber to /scan topic, following is the cpp code
```bash
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

void callbackScan(const sensor_msgs::LaserScan::ConstPtr& scan_data) {
  float min_distance = *std::min_element(scan_data->ranges.begin(), scan_data->ranges.end());
  ROS_INFO("Smallest distance: %.2f meters", min_distance);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "my_subscriber_node");
  ros::NodeHandle nh;
  std::string scan_topic;
  int queue_size;

  nh.param<std::string>("scan_topic",scan_topic,"/scan");
  nh.param<int>("queue_size",queue_size,10);
  ros::Subscriber subscriber = nh.subscribe(scan_topic, queue_size, callbackScan);
  ros::spin();
  return 0;
}
```
5) Then create a parameter file with extension .yaml including the topic name and the queue size
```bash
scan_topic: /scan
queue_size: 10
```
6) Place the subsriber node folder in ~/Workspaces/smb_ws/smb_highlevel_controller/src/.

7) Create a folder named config in the smb_highlevel_controller package and place the parameter file inside it.

8) Create a folder named launch in the smb_highlevel_controller package, modify the launch file in assignment 1, and place it inside this folder. The modified launch file is as below.
```bash
<?xml version="1.0" encoding="utf-8"?>
<launch>
    <arg name="laser_enabled" default="true"/>

    <include file="$(find smb_gazebo)/launch/smb_gazebo.launch">
        <arg name="laser_enabled" value="$(arg laser_enabled)"/>
    </include>

    <node name="smb_highlevel_controller" pkg="smb_highlevel_controller" type="my_subscriber_node" output="screen">
        <rosparam command="load" file="$(find smb_highlevel_controller)/config/scan_subsriber_params.yaml"/>
        </node>

        <node name="rviz" pkg="rviz" type="rviz" args="-d $(find smb_highlevel_controller)/rviz/default.rviz" output="screen"/>
    
</launch>
```
9) Now, open your terminal. You can clean anything previously built using
```bash
catkin clean
```
Then you can build the smb_highlevel_controller and resource setup files
```bash
catkin build smb_highlevel_controller
source ../devel/setup.bash
```
10) Then launch the package using
```bash
roslaunch smb_highlevel_controller my_highlevelController_launch.launch
```
11) After launching, don't forget to switch the Fixed Frame to odom in Rviz. Then click on `Add` at the bottom left of Rviz, then select `by topic` and select the /scan topic. You can add some objects in front of the robot in gazebo to see their laserscan in Rviz. 