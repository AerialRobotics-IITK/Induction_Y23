catkin build
source ../devel/setup.zsh
rosnode kill -a
roslaunch smb_highlevel_controller smb_highlevel_controller_launch.launch
