## ROS Assignment 1

##### Get to know ROS by inspecting the simulation of a Super Mega Bot (SMB) robot

[You can find the questions here](https://ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2021/lec1/Exercise%20Session%201.pdf)

### 1. Setup the SMB simulation:

- First you need ros installed on your system. Here I have used *ros-noetic* on ubuntu 20.04 on virtual box

- Download the zip file. Create a _Workspace_ directory in your home. (makes it organised)

- **To build a CATKIN workspace**
    - Install catkin tools for python3 in your home directory using
   
      `sudo apt-get install python3-catkin-tools python3-catkin-pkg`
  
    - To build the workspace run the following commands in the _Workspace_ directory.

      `source /opt/ros/noetic/setup.bash`
      
      `mkdir -p ~/smb_ws/src`
      
      `cd smb_ws/`
      
      `catkin build`

      `echo $ROS_PACKAGE_PATH` To check your workspace. This should return __/opt/ros/noetic/share__

- **To build a SYMLINK**
    - Run the following commands
      
      `cd Workspaces/smb_ws/src`

      `ln -s ~/git/smb_common/` enter location of your downloaded zip file here

      `ls -all` use this to confirm if the symlink was created sucessfully
      
- **To compile and BUILD the package**
    - Within the *~/Workspaces/smb_ws/src* directory run the following commands to congifure catkin environment.
    
      `source devel/setup.bash` To source your workspace.

      `source /opt/ros/noetic/setup.bash` To source ros

      `catkin config`

      ![configout](https://github.com/vd-0711/Induction_Y23/assets/94589050/53b90dc0-3cbb-4040-ae79-d2eb78656122)

    - Now enter the linked *smb_common* directory and run the commands to build the package.

      `catkin build smb_gazebo`

    - Error Handling :
      This may give an error as shown below. To solve this we need to install the required packages using `sudo apt install hector_gazebo_plugins` in the *src* directory itself. Don't forget to update your environment with `source ../devel/setup.bash`
             
       ![error1](https://github.com/vd-0711/Induction_Y23/assets/94589050/88fa74cd-b1c1-47ff-a2c8-8d5076b9310c)

--------------------------

### 2. Launching and Inspection

- Start a ros master using `roscore` in the *smd_common* directory. In a new terminal window run the following commands.
- Start the simulation using `roslaunch smb_gazebo smb_gazebo.launch`

- `rosnode list` output :
  
```
/base_controller_spawner
/gazebo
/gazebo_gui
/rosout
/smb_robot_state_publisher
```

- `rostopic list` output :

```
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

- `rostopic echo [topic]` This command must be run while the gazebo simulation is working since otherwise the clock does no publish any messages. You can also additionally run `rostopic list |xargs -n 1 rostopic info` to get info about all the active topics at once. After running `rostopic echo /imu0` a continuous series of data in the following format is given.

```
---
header: 
  seq: 115155
  stamp: 
    secs: 288
    nsecs: 900000000
  frame_id: "imu_link"
orientation: 
  x: 2.55184540299276e-09
  y: 1.515211468718363e-08
  z: -1.698043182364539e-06
  w: 0.9999999999985584
orientation_covariance: [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
angular_velocity: 
  x: 0.0
  y: 0.0
  z: 0.0
angular_velocity_covariance: [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
linear_acceleration: 
  x: -2.959185669299018e-07
  y: 4.9935847207772185e-08
  z: 9.80000000037622
linear_acceleration_covariance: [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
---

```

![rostopic_echo](https://github.com/vd-0711/Induction_Y23/assets/94589050/0c2e9298-ca22-4f49-8faf-a1d2077d16cf)

- `rostopic hz /imu0` output: gives frequency between most recent messages

```
subscribed to [/imu0]
WARNING: may be using simulated time
average rate: 393.939
	min: 0.000s max: 0.006s std dev: 0.00119s window: 391
average rate: 393.909
	min: 0.000s max: 0.009s std dev: 0.00123s window: 777
average rate: 393.194
	min: 0.000s max: 0.009s std dev: 0.00121s window: 1168
average rate: 392.839
	min: 0.000s max: 0.009s std dev: 0.00121s window: 1559
average rate: 392.663
	min: 0.000s max: 0.013s std dev: 0.00122s window: 1949
average rate: 392.533
	min: 0.000s max: 0.013s std dev: 0.00121s window: 2335
average rate: 392.451
	min: 0.000s max: 0.013s std dev: 0.00120s window: 2725
average rate: 392.362
	min: 0.000s max: 0.013s std dev: 0.00120s window: 3114
average rate: 392.350
	min: 0.000s max: 0.013s std dev: 0.00121s window: 3509
average rate: 392.303
	min: 0.000s max: 0.013s std dev: 0.00121s window: 3895
average rate: 392.299
	min: 0.000s max: 0.013s std dev: 0.00121s window: 4290
average rate: 392.343
	min: 0.000s max: 0.013s std dev: 0.00121s window: 4336
```

- `rqt_graph` output gives the ROS computation graph as shown

![rqt_grpah](https://github.com/vd-0711/Induction_Y23/assets/94589050/73b029aa-5f8a-4585-b56a-48445c540095)

----------------------

### 3. Command Desired Velocity from the terminal

`rostopic pub -r 10 /cmd_vel geometry_msgs/Twist  '{linear:  {x: 0.7, y: 0.0, z: 0.0}, angular: {x: 0.0,y: 0.0,z: 5.0}}'`

----------------------

### 4. Use keyboard to control

- Download teleop keyboard using `sudo apt-get install ros-noetic-teleop-twist-keyboard`
- Start the keyboard while the simulation is running using `rosrun teleop_twist_keyboard teleop_twist_keyboard.py`
- Make sure terminal window is active and not gazebo otherwise the teleop keyboard will not detect inputs.
  
[Screencast from 12-06-24 01:08:28 AM IST.webm](https://github.com/vd-0711/Induction_Y23/assets/94589050/524cf40c-c56f-48f7-b0b4-7d4fed8fadb6)

--------------------

### 5. Simulate a different world

- Go to *smb_common/smb_gazebo/launch* directory and edit the contents of the launch file so as to change the name of the world arg to any world found in *smb_gazebo/worlds* folder.

![Screenshot from 2024-06-12 01-25-44](https://github.com/vd-0711/Induction_Y23/assets/94589050/7d6c6d15-e154-4025-a0c6-1c7079796f5b)

- Run the simulation same was as earlier using `roslaunch smb_gazebo smb_gazebo.launch` You should see a similar line in the output. The simulation will take some time to load the first time.

![Screenshot from 2024-06-12 01-25-23](https://github.com/vd-0711/Induction_Y23/assets/94589050/a9cd860f-f06d-4ad4-ba9e-8d2294ae4e2c)

- Voila!

![Screenshot from 2024-06-12 01-25-10](https://github.com/vd-0711/Induction_Y23/assets/94589050/f41f7850-d551-4ec8-b3a9-f750a1327839)


