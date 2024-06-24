
# SMB Gazebo Simulation Guide

## Setting Up the Environment

1. Source the workspace:
    ```bash
    source devel/setup.bash
    ```

2. Launch the Gazebo simulation:
    ```bash
    roslaunch smb_gazebo smb_gazebo.launch
    ```

3. List active ROS nodes:
    ```bash
    rosnode list
    ```
    Expected output:
    ```
    /base_controller_spawner
    /gazebo
    /gazebo_gui
    /rosout
    /smb_robot_state_publisher
    ```

4. List active ROS topics:
    ```bash
    rostopic list
    ```
    Expected output:
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

5. Echo the clock topic:
    ```bash
    rostopic echo /clock
    ```
    Expected output:
    ```
    clock: 
      secs: 405
      nsecs: 532000000
    ---
    clock: 
      secs: 405
      nsecs: 533000000
    ```

6. Get information about the clock topic:
    ```bash
    rostopic info /clock
    ```
    Expected output:
    ```
    Type: rosgraph_msgs/Clock
    Publishers: 
     * /gazebo (http://Ubuntu20:38511/)
    Subscribers: 
     * /rosout (http://Ubuntu20:34993/)
     * /smb_robot_state_publisher (http://Ubuntu20:39761/)
     * /base_controller_spawner (http://Ubuntu20:36055/)
     * /gazebo (http://Ubuntu20:38511/)
     * /gazebo_gui (http://Ubuntu20:45813/)
    ```

7. Measure the frequency of the clock topic:
    ```bash
    rostopic hz /clock
    ```
    Expected output (subscribes to the clock):
    ```
    average rate: 954.993
        min: 0.001s max: 0.007s std dev: 0.00036s window: 680
    ```

8. Visualize the nodes and topics using `rqt_graph`:
    ```bash
    rqt_graph
    ```

## Publishing Velocity Commands

1. Publish a velocity command:
    ```bash
    rostopic pub /cmd_vel geometry_msgs/Twist "{linear: {x: 0.5, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.0}}" -r 3
    ```

2. Install and use `teleop_twist_keyboard` for controlling the robot:
    ```bash
    sudo apt-get install ros-noetic-teleop-twist-keyboard
    rosrun teleop_twist_keyboard teleop_twist_keyboard.py
    ```
    Note: The robot moves only if the terminal is the active window.

## Launching a Custom World

1. Create a new launch file in the `launch` directory of `smb_gazebo`:
    ```xml
    <launch>
        <include file="$(find smb_gazebo)/launch/smb_gazebo.launch">
            <arg name="world_file" value="/usr/share/gazebo-11/worlds/robocup14_spl_field.world"/>
        </include>
    </launch>
    ```

2. Launch the new world:
    ```bash
    roslaunch smb_gazebo <your_new_launch_file>.launch
    ```
