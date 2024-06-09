# Assignment 3 (ETHZ Exercise 1)

Download the smb_common zip file from ethz website and put the unzipped file in the local repo ~/git

Make a common workspace with a special sub workspace for smb_ws for out task and a mandatory src folder, using the command...

*mkdir -p ~/ws/smb_ws/src*

Make a symbolic link or symlink in the src folder of the unzipped smb_common folder in local git repo..
(for easier management of the packages without things getting messy),
using the command (make sure you are in the src directory)...

*ln -s ~/git/smb_common*

In the smb_ws run the command...

*catkin build*

Source the setup.bash file using the command...

*source devel/setup.bash*

Run the built smb_gazebo package using the command...

*roslaunch smb_gazebo smb_gazebo.launch*

Open another terminal to analyse the running nodes and topics

To get the list of running nodes use the command...

*rosnode list*

Similarly to get the list of all topics, use the command...

*rostopic list*

We know that to give command using the *rostopic pub* command we need the name of the topic to which /gazebo node subscribes
to via the /cmd_vel topic, we find the list of such topics by using the command...

*rostopic list | grep cmd_vel*

Checking the info for the above results using the command...

*rostopic info /topic_name*

We get to know that our topic of intereast is /cmd_vel

We can give a command to smb using the following command(sample)
(This makes it move in a circle)...

*rostopic pub /cmd_vel geometry_msgs/Twist "linear: x : 0.1 y : 0.0 z : 0.0 angular: x : 0.0 y : 0.0 z : 0.1"*

To use the teleop_twist_keyboard (and compile it from source as mentioned in the exercise),
use the command...

In your local git repo...

*git clone https://github.com/ros-teleop/teleop_twist_keyboard*

And create a symbolic link for this directory in the src folder of your workspace using...

*ln -s ~/git/teleop_twist_keyboard*

Don't forget to run the *catkin build* command from the workspace and source the setup.bash file using the 
*source devel/setup.bash* command

To verify that the teleop_twist_keyboard is compiled from source, use the command...

*roscd teleop_twist_keyboard*

Here are some images of the teleop_twist_keyboard being used...

## Launch File

The launch file (although buggy) in included with this directory.

I tried to rectify the error for quite some time, but the launch file was still showing errors on being launched.

So I attched a screenchot of the error message being displayed.
