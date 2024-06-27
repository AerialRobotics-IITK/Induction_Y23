## Target of the exercise 1 : Setup for smb simulation
Since we are currently using ubuntu 22.04 we need to use a docker image tu run ros noetic since ROS 1 is not supported in 22.04 .<br/><br/>
So we first of all install docker on linux(I already had the application installed from the store itself).<br/><br/>
Then we run the following command to pull the image of the ros-noetic :
    `docker pull ros:noetic-robot`<br/><br/>
Sometimes it might be possible that the error is showing : check if docker daemon is running. In that case first we need to stop any running containers first after opening docker application.<br/><br/>
Then to run the image of the docker we run the following command :
    `docker run -it ros:noetic-robot`<br/><br/>

This should probably start the docker container with some id.<br/><br/>
Now to start the master on the terminal run roscore.<br/><br/>
This will start the master node. Now to run any further commands we need to open a new terminal and connect it to this particular running terminal.<br/><br/>    
To do this we run the command : `docker ps ` to list the running containers while adding `-a` to the command will show all the containers. We copy the id of the runnning container, there will only be a single running container since we closed any prior running container before we ran the docker image.<br/><br/>
Now in this image we create a folder named git using : `mkdir ~/git`<br/><br/>
Within this folder we download the folder name `smb_common` from the course website and place it in this folder after unzipping it : `unzip filename.zip -d ~/git` <br/><br/>
This will place the file in the git folder after unzipping it.<br/><br/>
Now we create a directory where we will run all our commands : `mkdir ~/ws/smb_ws/src`<br/><br/>
In this directory we create a symlink between the file we have downloaded and the directory using the command :
`ln -s ~git/smb_common ~/ws/smb_ws/src `<br/><br/>
I found out through surfing that there are some dependencies that are required to be installed : 
`sudo apt install -y ros-noetic-velodyne-description<br/><br/>


Since we are using a docker image I first needed to install catking using the command : `sudo apt update`<br/><br/>
                                                                                        `sudo apt install catkin`<br/><br/>
Now we compile the package using the command : `catkin build smb_gazebo` after entering the directory ws/smb_ws<br/><br/>
Now we need to launch the simulation for inspecting the created nodes and their topics, for launching the simulation we use the command : `roslaunch smb_gazebo smb_gazebo.launch`<br/><br/>
Now for inspecting the created nodes and topics we need to open a new terminal and source the setup in the new terminal using the command :     `source /opt/ros/noetic/setup.bash` --> This command ensures that the various ros tools are available in the new terminal<br/><br/>
Now inside this new terminal we run the commands `rosnode list`<br/>
`rostopic echo [TOPIC]`<br/>
`rostopic hs [TOPIC]`<br/>
`rqt_graph`<br/>
as mentioned in the exercise pdf --> these commands allow us to list all the active topics,echoes or prints the messages being published on a specified topic to the console, displays the publishing rate of a specified topic and opens a GUI that displays a ROS computation graph which opens a new window displaying a graphical representation of your ROS nodes and topics.<br/><br/>
After this we can command a velocity to the robot from the terminal :<br/>
If we want to just publish a single message we use the command : `rostopic pub /cmd_vel geometry_msgs/Twist '{linear: {x: 0.5, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.5}}'`<br/>
If we want publish the velocity at a certain rate we use the following command : <br/>
`rostopic pub -r 10 /cmd_vel geometry_msgs/Twist '{linear: {x: 0.5, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.5}}'`<br/>
Here 10 is the frequency at which velocity is being published (in Hertz)<br/><br/>.
Then to control the robot using keyboard commands we need to use the teletop_twist_keyboard package, to use it we first clone the repository from the link : `https://github.com/ros-teleop/teleop_twist_keyboard.git` into the ~/git folder.<br/><br/>
Then we use similar commands just like we used for the smb_gazebo package to build this keyboard package followed by sourcing it.<br/><br/> 
Then we run the package using the command : `rosrun teleop_twist_keyboard teleop_twist_keyboard.py`<br/><br/>
Followed by this a ROS node is started which waits for keyboard commands and also displays the commands which can be used to control the command.<br/><br/>







