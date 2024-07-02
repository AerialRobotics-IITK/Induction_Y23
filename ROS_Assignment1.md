# ROS Assignment 1  
  
To start docker container with ros, ran `docker run -it ros:noetic-robot`  
To setup catkin, ran   
> apt-get update && apt-get install -y python3-catkin-tools  
> source /opt/ros/noetic/setup.bash &&\   
> mkdir -p ~/catkin_ws/src &&\   
> cd ~/catkin_ws/src &&\   
> catkin_init_workspace &&\   
> cd ~/catkin_ws &&\   
> catkin build
     
Then sourced using source ~/catkin_ws/devel/setup.bash  
  
## Question 1  
  
Downloaded the smb_commons zip file and extracted it     
Created folder /root/git in the container    
Used `docker cp` command to copy the folder to /root/git     
Then symlinked the folder to catkin workspace using `ln -s /root/git/smb_common/ ~/catkin_ws/src/`  

Ran `rosdep install --from-paths src --ignore-src -r -y` and `sudo apt install ros-noetic-gazebo-plugins` to install dependencies   
Then `catkin build smb_gazebo` to build the package    
`source devel/setup.bash` and then `roslaunch smb_gazebo smb_gazebo.launch`  

## Question 2

Executed the commands given in the question   
Displayed the nodes and topics   

## Question 3

Knowing the name of the topics, checked the type of the message in /smb_velocity_controller/cmd_vel
using `rostopic info /smb_velocity_controller/cmd_vel`      
Came out to be geometry_msg/Twist    
Ran `rosmsg show geometry_msgs/Twist`   
> geometry_msgs/Vector3 linear   
    float64 x   
    float64 y   
    float64 z   
> geometry_msgs/Vector3 angular   
    float64 x   
    float64 y   
    float64 z

Used command `rostopic pub ` to command a desired velocity 
`rostopic pub /cmd_vel geometry_msgs/Twist "{linear: {x: 5.0, y: 3.0, z: 4.0}, angular: {x: 0.0, y: 0.0, z: 0.0}}" -r 20`    

## Question 4

Git cloned [repo](https://github.com/ros-teleop/teleop_twist_keyboard)  
Then followed similar steps as in question to build package teleop_twist_keyboard  
Ran it using `rosrun teleop_twist_keyboard teleop_twist_keyboard.py`  

## Question 5

Navigate to the folder ~/catkin_ws/src/smb_common/smb_gazebo/launch  
Then `cat smb_gazebo.launch` reveals the contents of the launch file where the argument of the world_file node was changed to worlds/robocup14_spl_field.world  
Relaunched with `roslaunch smb_gazebo smb_gazebo.launch`








