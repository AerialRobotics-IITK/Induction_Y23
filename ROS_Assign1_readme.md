># RUNNING ROS after installing docker 
>
> - As we all have ubuntu 22.04 we werent able to directly install ros as listed in its official documentation http://wiki.ros.org/Installation/Ubuntu  , we had to first install docker and then work on ros's image on the docker 
> - we installed docker using the instructions listed in http://wiki.ros.org/docker/Tutorials/Docker
> - then to pull up an image of ros-noetic , the ros image we will be using in a container , we ran the following two commands 
> - docker pull ros:noetic-robot
> - docker run -it ros:noetic-robot
> - We also have the option of running all of this setup using wsl in windows. For that we can simply download docker desktop and open it while , within the wsl we pull the image of ros-noetic . But ros is a very heavy program and might cause problems in working within wsl in the future . 

># CONNECTING TWO TERMINALS 
> - after this we run roscore on this terminal , so that the master starts running on this terminal 
> - then we open a new terminal and check the name of the container runnign in docker using ---> docker ps 
> - we then run ----> docker exec -it <container_name> bash to connect the original terminal to the new terminal , such that the second terminal also has acess to the docker container now 
> - we then ---->sudo apt update , so that all packages are updated 
> - and ----->sudo apt-get install -y python3-rosdep so that dependecies we might need in the future are also installed 
> - we also do---> apt-get install -y ros-noetic-roscpp-tutorials ros-noetic-turtlesim , as these packages will come in use in the future

># EXCERCISE 1 
> - In this we first create the required folder using ---> mkdir ~/git
> - we then make a file structure of the form ~/Workspaces/smb_ws/src using mkdir
> - we then download curl using ----> sudo apt-get install curl
> - similarly unzip using ----> sudo apt-get install unzip
> - we then using curl download the smb file available as a link to a zip on the site (https://ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2021/lec1/smb_common.zip)
> - and unzip it to acess the smb-gazebo file 
> - then create a symlink of the smb-gazebo file in the ~/Workspaces/smb_ws/src using ---->  ln -s /path/to/file /path/to/symlink
> - Compile the smb_gazebo package using catkin ----> 
cd ~/Workspaces/smb_ws
catkin build
> - Using roslaunch to start the simulation and inspect the created nodes and their topics.
> - Source the ROS setup script
source /opt/ros/noetic/setup.bash
    Launch the simulation
roslaunch smb_gazebo smb_gazebo.launch
In a new terminal, source the ROS setup script again
source /opt/ros/noetic/setup.bash
    List all active nodes 
rosnode list
    List all active topics
rostopic list
    Echo messages from a specific topic (e.g., /cmd_vel)
rostopic echo /cmd_vel
    Check the publishing rate of a specific topic (e.g., /cmd_vel)
rostopic hz /cmd_vel
    Visualize the ROS computation graph
rqt_graph
> - Publish a velocity command to the /cmd_vel topic
rostopic pub /cmd_vel geometry_msgs/Twist "linear:
  x: 0.5
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 0.5" -r 10
> - Navigate to the git folder and clone the repository
cd ~/git
git clone https://github.com/ros-teleop/teleop_twist_keyboard.git
  Create a symlink in the catkin workspace
cd ~/Workspaces/smb_ws/src
ln -s ~/git/teleop_twist_keyboard .

   Compile the package
cd ~/Workspaces/smb_ws
catkin_make
   Run teleop_twist_keyboard
source devel/setup.bash
rosrun teleop_twist_keyboard teleop_twist_keyboard.py
> - <!-- File: smb_custom_world.launch -->
<launch>
  <!-- Include the default smb_gazebo.launch file -->
  <include file="$(find smb_gazebo)/launch/smb_gazebo.launch">
    <!-- Override the world_file argument to use a different world -->
    <arg name="world_file" value="/usr/share/gazebo-11/worlds/robocup14_spl_field.world"/>
  </include>
</launch>
> - Check if teleop_twist_keyboard is compiled
roscd teleop_twist_keyboard
> - Source the ROS setup script
source /opt/ros/noetic/setup.bash
    Start the custom launch file
roslaunch smb_gazebo smb_custom_world.launch




