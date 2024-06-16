# ROS #

### Exercise Session 2

### **1, 2, 3)**   

Downloaded ***smb_highlevel_controller*** file
and inspected ***CMakelists.txt*** and  ***package.xml*** files.

> Click on the files below to see their content :   
<a href="./files/smb_highlevel_controller/CMakeLists.txt">CMakelists.txt</a>   
<a href="./files/smb_highlevel_controller/package.xml">package.xml</a>

<hr>                    

### **4,5,6 )**

created a ***config*** folder inside  ***smb_highlevel_controller***. Inside ***config*** added the following default values in ***default.yaml***:
```
subscriber_topic: /scan
queue_size: 100
```
> click to see <a href="./files/smb_highlevel_controller/config/default.yaml">default.yaml</a>   

Now to create a subscriber to the topic `/scan` I made changes in the ***SmbHighlevelController.cpp*** file. I added a `readParameters()` function to get the default parameters  and to return false if the parametes doesn't exist. then I subscribed to the topic while also passing a callback `scanCallback` function which outputs the smallest distance measurement from the vector *ranges* in the message of the laser scanner to the terminal.

> click to see <a href="./files/smb_highlevel_controller/src/SmbHighlevelController.cpp">SmbHighlevelController.cpp</a>

<hr>

### **7, 8, 9)**

Created a ***launch*** folder inside ***smb_highlevel_controller*** and added the launch file ***mylaunchfile*** from Exercise 1 to the folder. In the next step I modified the launch file to include **smb_highlevel_controller** node, load the parameters and to pass the argument **laser_enabled** to the
**smb_gazebo.launch** file with value *true*.
At last  I added **RViz** to the launch file and renamed it to ***mylaunchfile(modified).launch***.

> click to see <a href="./files/smb_highlevel_controller/launch/mylaunchfile(modified).launch">mylaunchfile(modified).launch</a>

<hr>
<br>
<br>

But the story doesn't end here. I also had to declare the functions and variables I used in the ***SmbHighlevelController.cpp*** file to its header file ***SmbHighlevelController.hpp***. 
> click to see <a href="./files/smb_highlevel_controller/include/smb_highlevel_controller/SmbHighlevelController.hpp">SmbHighlevelController.hpp</a>

<hr>
<br><br>

# Pics 
