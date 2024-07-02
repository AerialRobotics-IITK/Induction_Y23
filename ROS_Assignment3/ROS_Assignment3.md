# ROS Assignment 3

## Question 1,2

The package was downloaded, symlinked and compiled after which the new worls was moved to the worlds folder  
Then the [modified launch file](/ROS_Assignment3/mylaunch.launch) was added to the launch folder with the new world   
The node KeyboardTwist was removed as instructed   

## Question 3,4,5  

Created a node called [node.cpp](/ROS_Assignment3/node.cpp)   
The Laserscan message consists of the attributes angle_min, angle_max, angle_increment, and ranges  
These ranges array is populuated by taking distance measurements to the nearest obstacle found at each angular position between the min and max with respect to the robot (polar coordinate of the obstacle with respect to the robot)  
> The subscriber gathers info about the position of the pillar with respect to the robo  
> Then the velocity necessary to push the robot towards the pillar is calculated from the errors in angle and distance and published     

Then modified the launch file further to make sure the pillar is well visible  

