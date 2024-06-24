For 1st ques:-
First created a gir folder and extracted smb_commmon zipped folder in it. Then created the workspace folder and inside it a smb_ws named folder. Inside smb_ws folder created a src folder and then inside src folder symlinked the smb_common package in it. Then changed directory to smb_ws and run the command "catkin_make" which created the build and devel folder..
For 2nd ques:-
Launch the smb_gazebo package using commabd "roslaunch smb_gazebo smb_gazebo.launch". It launched several nodes and a gazebo simulator.
After the package is launched used rosnode list and rostoic list to find the running node and list
Then used rostopic echo /cmd_vel to check what is being published to /cmd_vel topic
Then used rqt_graph to check all nodes and topics
For 3rd ques:-
Used rostopic pub /cmd_vel geometry_msgs/Twist "Linear: X:0.0
							y:1.0
							z:0.0
						angular:
							x:0.0
							y:0.0
							z:1.0"
Using this command the bot started moving circle on the gazebo
For 4th ques:-
Have cloned teleop_twist_keyboard git repo through git clone.
Then launches teleop_twist_keyboard node using "rosrun teleop_twist_keyboard teleop_twist_keyboard .py"
Through this command we can move bot through the keys on our keyboard. We can visualize the motion on gazebo
For 5th ques:-
Created a launch file which will launch gazebo launch but with change in world argument to the environmnet given in ques.

<launch>
<include file="$(find smb_gazebo)/launch/smb_gazebo.launch">
        <arg name="world_file" value="/usr/share/gazebo-11/worlds/robocup14_spl_field.world"/>
 </include>
</launch>
