sunraj@sunraj-MacBookAir:~/catkin_ws$ rosnode list
/base_controller_spawner
/gazebo
/gazebo_gui
/pointcloud_to_laserscan
/rosout
/rviz
/smb_highlevel_controller
/smb_robot_state_publisher
/twist_mux


sunraj@sunraj-MacBookAir:~/catkin_ws$ rostopic list
/clicked_point
/clock
/cmd_vel
/diagnostics
/e_stop
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
/initialpose
/joint_states
/joy_teleop/cmd_vel
/move_base_simple/goal
/odom
/rosout
/rosout_agg
/rslidar_points
/scan
/smb_velocity_controller/cmd_vel
/smb_velocity_controller/odom
/smb_velocity_controller/parameter_descriptions
/smb_velocity_controller/parameter_updates
/tf
/tf_static
/twist_marker_server/cmd_vel
/visualization_marker
/visualization_marker_array


sunraj@sunraj-MacBookAir:~/catkin_ws$ rostopic echo cmd_vel
linear:
  x: 0.0
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 0.0
---
linear:
  x: 0.0
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 0.0
---
linear:
  x: 0.0
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 0.0
---
linear:
  x: 0.0
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 0.0
---
linear:
  x: 0.0
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 0.0
---


sunraj@sunraj-MacBookAir:~/catkin_ws$ rostopic hz cmd_vel
subscribed to [/cmd_vel]
WARNING: may be using simulated time
no new messages
average rate: 9.852
	min: 0.101s max: 0.102s std dev: 0.00050s window: 3
average rate: 9.494
	min: 0.101s max: 0.113s std dev: 0.00544s window: 4
average rate: 9.569
	min: 0.101s max: 0.113s std dev: 0.00492s window: 5
average rate: 9.506
	min: 0.101s max: 0.113s std dev: 0.00462s window: 6




sunraj@sunraj-MacBookAir:~/catkin_ws$ rostopic pub /cmd_vel geometry_msgs/Twist '[0.5,0,0]' '[0,0,0]'
publishing and latching message. Press ctrl-C to terminate