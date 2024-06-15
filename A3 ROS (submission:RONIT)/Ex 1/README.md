
# ROS #

### Exercise Session 1

### **1)**

Followed the instruction and created all the needed folders, then using the command   
```
> ln -s ~/git/smb_common/ ~/Workspaces/smb_ws/src
```   
created symlink.

executing ``` > catkin build smb_gazebo``` in ***smb_ws***, I built the gazebo package.
Then all that was left is to source and run the package with the commands given below:   
```
> source devel/setup.bash 
> roslaunch smb_gazebo smb_gazebo.launch
```

<hr>

### **2)**

Inspecting the created nodes and their topic:

```
> rosnode list
/base_controller_spawner
/gazebo
/gazebo_gui
/rosout
/smb_robot_state_publisher
```

```
> rostopic list
/clock
/cmd_vel
/gazebo/link_states
/gazebo/model_states
/gazebo/parameter_descriptions
/gazebo/parameter_updates
/gazebo/performance_metrics
/gazebo/set_link_state
/gazebo/set_model_state
/gazebo_ros_control/pid_gains/LF_WHEEL_JOINT/parameter_descriptions
/gazebo_ros_control/pid_gains/LF_WHEEL_JOINT/parameter_updates
/gazebo_ros_control/pid_gains/LH_WHEEL_JOINT/parameter_descriptions
/gazebo_ros_control/pid_gains/LH_WHEEL_JOINT/parameter_updates
/gazebo_ros_control/pid_gains/RF_WHEEL_JOINT/parameter_descriptions
/gazebo_ros_control/pid_gains/RF_WHEEL_JOINT/parameter_updates
/gazebo_ros_control/pid_gains/RH_WHEEL_JOINT/parameter_descriptions
/gazebo_ros_control/pid_gains/RH_WHEEL_JOINT/parameter_updates
/imu0
/imu0/accel/parameter_descriptions
/imu0/accel/parameter_updates
/imu0/bias
/imu0/rate/parameter_descriptions
/imu0/rate/parameter_updates
/imu0/yaw/parameter_descriptions
/imu0/yaw/parameter_updates
/joint_states
/odom
/rosout
/rosout_agg
/smb_velocity_controller/cmd_vel
/smb_velocity_controller/odom
/smb_velocity_controller/parameter_descriptions
/smb_velocity_controller/parameter_updates
/tf
/tf_static
```

```
> rostopic echo /smb_velocity_controller/odom
header: 
  seq: 21118
  stamp: 
    secs: 422
    nsecs: 977000000
  frame_id: "odom"
child_frame_id: "base_link"
pose: 
  pose: 
    position: 
      x: 0.0013051329938909718
``` 
and it kept on going......

```
> rostopic hz /smb_velocity_controller/odom
subscribed to [/smb_velocity_controller/odom]
WARNING: may be using simulated time
average rate: 50.051
	min: 0.019s max: 0.021s std dev: 0.00047s window: 50
average rate: 50.025
	min: 0.016s max: 0.024s std dev: 0.00075s window: 100
  ```
 and it kept on going.......

> ![alt text](./_1.png)


### **3)**


![alt text](./_2.png)

### **4)**
 clone the repo:
 ```
 > git clone https://github.com/ros-teleop/teleop_twist_keyboard.git
 ```
 create a symlink:
```
> ln -s ~/git/teleop_twist_keyboard/ ~/Workspace/smb_ws/src/
```
build the package but first move to ~/Workspaces/smb_ws:
```
> catkin build teleop_twist_keyboard 
```
run it:
```
> rosrun teleop_twist_keyboard teleop_twist_keyboard.py
```
### **5)**

launch file is attached for viewing.   
I have used ***big_map_summer_school.world***.   
Save the file in  ***launch*** folder inside ***smb_gazebo*** file.   
 navigate to that launch directory and use
```
> roslaunch mylaunchfile.launch
```
( I have named my file ***mylaunchfile.launch*** )

> ![alt text](./_3.png)
