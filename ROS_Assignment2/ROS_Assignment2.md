# ROS Assignment 2   

## Question 2

Downloaded the smb_highlevel_controller zip file, extracted it, copied it to root/git, symlinked it and compiled it using catkin     

## Question 3

Navigated to root/smb_highlevel_controller and inspected the given files using cat  
> [cat CMakeLists.txt](/CMakeLists.png)   
> [cat package.xml](/CMakeLists.png)  

## Question 4,5,6

Created [params.yaml](/ROS_Assignment2/params.yaml) in the config directory file with default value of /scan under topic name and 20 under queue size  
The node was subscribed to the /scan topic and a ros::Subscriber object was created with ScanCallBack as the callback function  

> View the [SmbHighlevelController.cpp](SmbHighlevelController.cpp) file  

## Question 7,8,9

As instructed in the question, the [launch file](/ROS_Assignment2/mylaunch.launch) was modified to:  
> run the smb_highlevel_controller node  
> load the parameter file (parameters unique to this node) with command-line override  
> pass the argument lazer_enabled to the smb_gazebo.launch with value true  
> launch the rviz package 

The header file [SmbHighlevelController.hpp](/ROS_Assignment2/SmbHighlevelController.hpp) was modified to update new methods and variables  

Then `catkin build smb_highlevel_controller` to build the package    
`source devel/setup.bash` and then `roslaunch smb_highlevel_controller mylaunch.launch`  