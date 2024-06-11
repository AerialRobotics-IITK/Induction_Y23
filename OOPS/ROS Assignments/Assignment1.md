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

      ![Required Output](configout.png)

    - Now enter the linked *smb_common* directory and run the commands to build the package.

      `catkin build smb_gazebo`

    - Error Handling :
      This may give an error as shown below. To solve this we need to install the required packages using `sudo apt install hector_gazebo_plugins` in the *src* directory itself. Don't forget to update your environment with `source ../devel/setup.bash`
             
       ![hector error](error1.png)

--------------------------

### 2. Launching and Inspection

- Start a ros master using `roscore` in the *smd_common* directory

