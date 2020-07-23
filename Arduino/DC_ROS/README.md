# Arduino DC ROS file
This is the arduino node code file that makes the arduino node subscribe to cmd_vel topic and pass the data to motors to move Asemo using remote keyboard, while moving the robot it publishes its odometry to the remote laptop to calculate and locate Asemo. It is connected to ros nodes using  [ ros_serial package](http://wiki.ros.org/rosserial_arduino/Tutorials) . This code is simplified by means of [adafruit library](https://github.com/adafruit/Adafruit-Motor-Shield-library) . 

### Moving Asemo
to move asemo first run  `roscore` on the host computer, networking between computers in ros system is discussed in the main documentation or in [this article](http://wiki.ros.org/ROS/Tutorials/MultipleMachines) then you should have ros_serial installed on your computer, if not install it from [here](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup)
install it then run it through the following commands.
 - on the device connected to the arduino -raspberry pi or pc- you need to specify the serial port which is connected to arduino and run the following command on the device connected to arduino **not sure**
 
```sh
rosrun rosserial_python serial_node.py /dev/ttyUSB*
```
or

    rosrun rosserial_python serial_node.py /dev/ttyACM*
    
Then on the remote computer run the following command to move the robot with remote keyboard
    
    rosrun teleop_twist_keyboard teleop_twist_keyboard.py  /turtel1/cmd_vel := cmd_Vel
this command is reading keyboard strokes and publish it cmd_vel which is handled by arduino node

Arduino node is subscribing [twist messages](http://docs.ros.org/diamondback/api/geometry_msgs/html/msg/Twist.html) from cmd_vel topic and excuiting motor move function, While Asemo moving the odometry will be published to 'encoder' topic .

### Subscribing from cmd_vel
 motors_cb function is executed for every new keyboard stroke is pressed and the data is passed as an argument which is calculated to linear velocity and angular velocity and then assigned to left and right motors by means of adafruit functions  `motorR.setSpeed(VR);` and  `motorR.run(FORWARD);` - in case of VR is >0 and if VR < 0  `motorR.run(BACKWORD);` - for the right motor and the same for the left
 
 ### Publishing to encoder topic
 Adafruit summarize all calculation for finding the location of Asemo to two function ` L_enc(PinA, pinB).read();` and ` R_enc(PinC, pinD).read();`. When the value of encoder changes the node updates the [Point32](http://docs.ros.org/melodic/api/geometry_msgs/html/msg/Point32.html) point_message variable and publish it through the following lines
 
 ```
Point_msg.x=RnewPosition;
Point_msg.y=LnewPosition;
enc_pub.publish(&Point_msg);
```


