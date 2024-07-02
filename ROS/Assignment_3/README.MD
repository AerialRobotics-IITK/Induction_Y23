# ROS Assignment 3  

Continued with VM of Ubuntu 20.04, used in assignment 1 & 2 
Did the following things to setup the machine:

## Question 1 

* Downloaded the smb_commons zip file and extracted it   
* Made soft link to the smb_common dir in git dir, to src dir
    ```bash
    ln -s ~/git/smb_common_v2 ~/Workspaces/smb_ws/src
    ```

 ## Question 2
 - Modified the [launch file](./src/smb_highlevel_controller/launch/Excercise_3.launch)
 ```xml
 <?xml version="1.0" encoding="utf-8"?>

<launch>
  <include file="$(find smb_gazebo)/launch/smb_gazebo.launch">
    <arg name="world_file" value="$(find smb_gazebo)/worlds/singlePillar.world"/>
    <arg name="laser_enabled" value="true"/>                        
  </include>
  <node name="pillar_controller" pkg="smb_highlevel_controller" type="pillar_detector" output="screen"/><!--Added pillar-->
    <rosparam command="load" file="$(find smb_highlevel_controller)/config/default.yaml" />
  <node pkg="rviz" type="rviz" name="rviz"/>
</launch>
```

 ## Question 3 & 4
* Created **subscriber** that subscribes to `/scan topic` in [pillar_detection.cpp](./src/smb_highlevel_controller/src/pillar_detection.cpp) and a **publisher** that publishes to `/cmd_vel`
    ```cpp
    ros::NodeHandle nh;

    // Initialize subscriber and publisher
    scan_subscriber_ = nh.subscribe("/scan", 10, &PillarController::CallBack, this);
    cmd_vel_publisher_ = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    ```  

* Made a callback function named ***CallBack*** in [pillar_detection.cpp](./src/smb_highlevel_controller/src/pillar_detection.cpp) that receives the scanned data,interprets it and then publish vel to cmd_vel 

 ## Question 5
 The logic of the P Controller is in the CallBack function itself
> Here is how it works:  
> - Finds the minimum distance stores it in **min_range** and its index which is stored in **min_index**
> - We use this **min_index** to find the angle by which we should rotate the robot along the z axis.
> - Multiplying by a factor Kp_ the angular velocity to increase its magnitude.
> - Publishing the results to /cmd_vel
> - The velocities become 0 , if **min_range<=0**

Here is the code:
```cpp
// Initialize min_range to a large value
        float min_range = std::numeric_limits<float>::infinity();
        int min_index = 0;

        // Iterate over the ranges to find the minimum valid range and its index
        for (size_t i = 0; i < in_msg.ranges.size(); ++i) {
            float range = in_msg.ranges[i];
            if (std::isfinite(range) && range < min_range) {
                min_range = range;
                min_index = i;
            }
        }

        // Calculate the angle of the closest point
        float angle = in_msg.angle_min + min_index * in_msg.angle_increment;

        // Create and populate the Twist message
        geometry_msgs::Twist msg;
        msg.linear.x = 1.0;  
        msg.angular.z = Kp_ * angle;  

        // Stop if an obstacle is too close
        if (min_range < 1.0) {
            msg.linear.x = 0.0;
            msg.angular.z = 0.0;
        }
        // Printing current linear and angular speed.
        ROS_INFO("Current Linear Speed: %f", msg.linear.x);
        ROS_INFO("Current Angular Speed: %f", msg.angular.z);
        // Publish the command
        cmd_vel_publisher_.publish(msg);
 ```

## RESULTS:

1. Output of the code as seen on Gazebo:  
[Gazebo Video](./Robot%20successfuly%20reaching%20pillar.mkv)
2. RViz visualization of the RobotModel and TF display  
[Rviz video](./Rviz.mkv)
