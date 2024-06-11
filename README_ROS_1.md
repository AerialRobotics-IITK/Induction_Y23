# Here are the steps to follow to complete the assignment 1
(Make sure you are using Ubuntu 20.04 version before following these steps.-)
1) Make a git directory and also setup a catkin workspace.
2) Download the smb_common zip file from the course website, unzip it and place the folder in git folder.
3) To make a symlink -
```bash
cd ~/Workspaces/smb_ws/src/
ln -s ~/git/smb_common/
```
4) Make sure to install the hector-gazebo packages in your smb_ws before building the smb_gazebo package
```bash
sudo apt-get update
sudo apt install ros-noetic-hector-gazebo-plugins
```
5) Re-enter your src folder and build the smb_gazebo package
```bash
catkin build smb_gazebo
```
Save your changes using
```bash
source ../devel/setup.bash
```
6) Before launching, install the velodyne_description package in your smb_ws
```bash
sudo apt install ros-noetic-velodyne-description
```
Save changes
```bash
source ../devel/setup.bash
```
Navigate to `~/Workspaces/smb_ws/src/smb_common` and then launch the smb_gazebo package
```bash
roslaunch smb_gazebo smb_gazebo.launch
```
7) To inspect the created node and topics, open a new terminal and source the ros setup
```bash
source /opt/ros/noetic/setup.bash
```
Then use the following commands to inspect
```bash
rosnode list
rostopic list
rostopic echo [TOPIC]
rostopic hz [TOPIC]
rqt_graph
```
8) Give the robot a desired velocity using `rostopic pub /cmd_vel` command. Eg-
```bash
rostopic pub -r 10 /cmd_vel geometry_msgs/Twist '{linear :{x: 0.05, y: 0, z: 0}, angular :{x: 0, y: 0, z: 0}}'
```
9) to install teleop_twist_keyboard use
```bash
sudo apt-get install ros-noetic-teleop-twist-keyboard
```
and then save changes 
```bash
source devel/setup.bash
```
Now, open a new terminal, source ros, and run teleop_twist_keyboard
```bash
rosrun teleop_twist_keyboard teleop_twist_keyboard.py
```
Now you can control your robot using your keyboard.

10) Now, to write a launch file, use any text-editor of your choice and write it. Below is the launch file to be written.
```bash
<?xml version="1.0" encoding="utf-8"?>
<launch>
    <!-- Include the smb_gazebo.launch file -->
    <include file="$(find smb_gazebo)/launch/smb_gazebo.launch">
        <!-- Change the world file argument -->
        <arg name="world_file" default="/usr/share/gazebo-11/worlds/robocup14_spl_field.world"/>
    </include>
</launch>
```
Place this launch file in `~/Workspaces/smb_ws/smb_common/smb_gazebo/launch/`, Navigate to ~/Workspaces/smb_ws and source from devel.
```bash
source devel/setup.bash
```

Then navigate to ~/Workspaces/smb_ws/smb_common and launch the new launch file
```bash
roslaunch smb_gazebo my_smb_simulation.launch
```
Now this can easily be controlled by keyboard by using teleop_twist_keyboard in other terminal as described above.