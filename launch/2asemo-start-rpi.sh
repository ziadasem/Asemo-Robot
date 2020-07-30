#!/bin/bash

#this file should be run evety time you want to start asemo on remote machine
#BUT you should run 1asemo-start.sh at least one time if you restart your router or change it

#CONNECTING TO ROS ENVIRONMENT
# reading ip address of the remote computer
read -p 'enter ip address of the remote computer, paste ip here ' uservar

#connecting to roscore in the remote computer
export ROS_MASTER_URI=http://$uservar:11311/

echo "" #new line

#STARTING ROS SERIAL
#ros serial need to specify the port connected to arduino 

#  Taking the port number, if the user doesn't know the port he should remove all cables and leave the arduino serial cable only and 
# _type *
read -p 'enter the serial port connected to arduino i.e (1,2 or 3) \n if you dont know remove all cables and let arduino serial cable only and type * '  number
if  [ -z "$number" ] # if user didn't type anything, i.e -z means isNull()
then
rosrun rosserial_python serial_node.py /dev/ttyACM*
else
rosrun rosserial_python serial_node.py /dev/ttyACM$number
fi #end if in shell


