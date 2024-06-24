## ROS ASSIGNMENT 2
Used catkin_create_pkg smb_highlevel_controller roscpp rospy to create a nw package in the workspace used in first assignmnet

Created a node inside src folder of smb_highlevel_controller pkg that subscribed to the /scan topic. It Subscribe to /scan and then call function scannerCallBack which take the message from topic and find the minimun distance of obstacle from the bot and use ROS_INFO to display that distance on terminal

Created a parameter file for the node

For the launch file, I have copied the launch file that was used in first assignment into the smb_highlevel_controllerpkg with some changes.

In the launch file I have added node that was created earlier than passed laser_enabled argument.

Further for the last part I have added rviz to the launch file and add an argument to find smb_highlevel_controller so that smb_highlevel_controller can be stimulated on rviz simulator.

