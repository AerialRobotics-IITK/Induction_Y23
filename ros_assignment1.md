-> In first question we first make a directory git using mkdir command (mkdir -p ~/git), then download the zip file and unzip it in the git directory . In the second step we setup our catkin workspace .Following the instruction in the question we firstly make directory /Workspaces/smb_ws/src and navigate to it using cd cmd .Then as mentioned in the question we create a symlink to the smb_common package using cmd (ln -s ~/git/smb_common .) . After this I compiled my workspace using catkin make using the following cmd (cd ~/Workspaces/smb_ws and then catkin_make) . 


-> In second question as mentioned in the question we firstly launch the file using (roslaunch smb_gazebo smb_gazebo.launch) and inspect different aspects like topic , nodes etc using their relevat cmds mentioned in the question . for finding topic name you can use (rostopic list).

-> Cmd for desired velocity (rostopic pub /smb_velocity_controller/cmd_vel geometry_msgs/Twist '{linear: {x: 0.5, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.5}}')

-> In fourth question we firstly clone the repository using git clone cmd then compile the package using the catkin and then run it using rosrun . 
(cd ~/git
git clone https://github.com/ros-teleop/teleop_twist_keyboard.git
cd ~/Workspaces/smb_ws/src
ln -s ~/git/teleop_twist_keyboard .
cd ~/Workspaces/smb_ws
catkin_make
rosrun teleop_twist_keyboard teleop_twist_keyboard.py
)


-> For launching the simulation in a different world we have to create a new launch file . So we will Create a new file named smb_custom_world.launch in the smb_gazebo/launch directory with the following content:
(<launch>
  <include file="$(find smb_gazebo)/launch/smb_gazebo.launch">
    <arg name="world_file" value="/usr/share/gazebo-11/worlds/robocup14_spl_field.world"/>
  </include>
</launch>)
Now we will run it with help of rosrun in world with the cmd (rosrun smb_gazebo smb_custom_world.launch).