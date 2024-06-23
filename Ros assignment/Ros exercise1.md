# Running ROS Noetic Using Docker on Ubuntu 22.04
## Overview

Used this guide which provides instructions for setting up and running ROS Noetic using Docker on Ubuntu 22.04. The steps cover installation, connecting terminals, and performing initial exercises with ROS.
Installation Steps
Step 1: Install Docker

    Follow the official ROS Docker tutorial for installing Docker.
    Verify the installation by checking Docker's version.

Step 2: Pull and Run the ROS Noetic Image

    Pull the ROS Noetic Docker image:
        docker pull ros:noetic-robot
    Run a container from the ROS Noetic image:
        docker run -it ros:noetic-robot

Step 3: Connecting Multiple Terminals

    Start ROS Master: In the running Docker container, start the ROS master:
        roscore
    Open a Second Terminal: To connect another terminal to the Docker container, find the container ID:
        docker ps
    Attach to the Running Container:
        docker exec -it <container_id> bash
    Update and Install Necessary Packages:
        sudo apt update
        sudo apt-get install -y python3-rosdep
        sudo apt-get install -y ros-noetic-roscpp-tutorials ros-noetic-turtlesim

Step 4: Exercise 1 - Setup and Simulation

    Create Directory Structure:
        mkdir -p ~/Workspaces/smb_ws/src
    Install Additional Tools:
        sudo apt-get install curl unzip
    Download and Extract smb_common:
        curl -L -o smb_common.zip https://ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2021/lec1/smb_common.zip
        unzip smb_common.zip -d ~/Workspaces/smb_ws/src
    Create Symlink for SMB Gazebo:
        ln -s ~/Workspaces/smb_ws/src/smb_common ~/Workspaces/smb_ws/src/smb_gazebo
    Build the Catkin Workspace:
        cd ~/Workspaces/smb_ws
        catkin build
    Launch the Simulation:
        source /opt/ros/noetic/setup.bash
        roslaunch smb_gazebo smb_gazebo.launch
    Inspect ROS Nodes and Topics:
        List all nodes: rosnode list
        List all topics: rostopic list
        Echo topic messages: rostopic echo /cmd_vel
        Check topic publishing rate: rostopic hz /cmd_vel
        Visualize ROS graph: rqt_graph
    Publish Velocity Command:
        rostopic pub /cmd_vel geometry_msgs/Twist "linear: x: 0.5 y: 0.0 z: 0.0 angular: x: 0.0 y: 0.0 z: 0.5" -r 10
    Clone and Build teleop_twist_keyboard:
        mkdir -p ~/git
        cd ~/git
        git clone https://github.com/ros-teleop/teleop_twist_keyboard.git
        ln -s ~/git/teleop_twist_keyboard ~/Workspaces/smb_ws/src
        cd ~/Workspaces/smb_ws
        catkin_make
    Run teleop_twist_keyboard:
        source devel/setup.bash
        rosrun teleop_twist_keyboard teleop_twist_keyboard.py
    Create and Use Custom Launch File:
        Create a custom launch file named smb_custom_world.launch with the following content:
        <launch>
      <include file="$(find smb_gazebo)/launch/smb_gazebo.launch">
        <arg name="world_file" value="/usr/share/gazebo-11/worlds/robocup14_spl_field.world"/>
      </include>
    </launch>
    Run the Custom Launch File:
        Launch custom world: roslaunch smb_gazebo smb_custom_world.launch.
    Verify teleop_twist_keyboard Compilation:
        Change directory: roscd teleop_twist_keyboard.
        Source setup script: source /opt/ros/noetic/setup.bash.


![alt](Ros assignment/WhatsApp Image 2024-06-23 at 11.37.36 PM.jpeg)
![alt](Ros assignment/WhatsApp Image 2024-06-23 at 11.44.27 PM.jpeg)



