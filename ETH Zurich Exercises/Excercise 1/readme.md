# Assignment 3 (ETHZ Exercise 1)

Download the smb_common zip file from ethz website and put the unzipped file in the local git repo ~/git

Make a common workspace with a special sub workspace  smb_ws for our task and a mandatory src folder, using the command...

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

<img width="950" alt="rosnode list" src="https://github.com/EarlOfHycia/Induction_Y23/assets/162675481/ed6c2f34-067e-4b82-a257-8f31de139f02">

Similarly to get the list of all topics, use the command...

*rostopic list*

<img width="950" alt="rostopic list" src="https://github.com/EarlOfHycia/Induction_Y23/assets/162675481/ceb3a525-814e-4237-9928-4805f5014662">

We know that to give command to move to smb using the *rostopic pub*, we need the name of the topic to which /gazebo node subscribes
to via the /cmd_vel topic, we find the list of such topics by using the command...

*rostopic list | grep cmd_vel*

<img width="950" alt="rostopic list | grep cmd_vel" src="https://github.com/EarlOfHycia/Induction_Y23/assets/162675481/47421fdc-0d06-41b4-b891-546a96e04de6">

Checking the info for the above results using the command...

*rostopic info /topic_name*

We get to know that our topic of interest is /cmd_vel

We can give a command to smb using the following command(sample)
(This makes it move in a circle)...

*rostopic pub /cmd_vel geometry_msgs/Twist "linear: x : 0.1 y : 0.0 z : 0.0 angular: x : 0.0 y : 0.0 z : 0.1"*

<img width="950" alt="rostopic pub :cmd_vel(1)" src="https://github.com/EarlOfHycia/Induction_Y23/assets/162675481/b9e78541-e6e2-4444-894a-a774fb079c75">

<img width="950" alt="rostopic pub :cmd_vel(2)" src="https://github.com/EarlOfHycia/Induction_Y23/assets/162675481/c8910d5d-d3dc-4fa2-8518-c690440a5294">

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

<img width="950" alt="roscd teleop_twist_keyboard" src="https://github.com/EarlOfHycia/Induction_Y23/assets/162675481/107954f4-03fe-4689-b7cc-1682bfa242cb">

Here are some images of the teleop_twist_keyboard being used...

<img width="950" alt="teleop_twist_keyboard" src="https://github.com/EarlOfHycia/Induction_Y23/assets/162675481/d3a888ac-c800-43fc-9a88-ac1634810043">

## Launch File

The launch file (although buggy) in included with this directory.

I tried to rectify the error for quite some time, but the launch file was still showing errors on being launched.

So I attched a screenchot of the error message being displayed.

<img width="950" alt="error" src="https://github.com/EarlOfHycia/Induction_Y23/assets/162675481/7838c3af-d5c4-43fc-81fb-a393b89dcba3">
