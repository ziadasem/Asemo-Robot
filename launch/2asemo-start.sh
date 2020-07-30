#!/bin/bash

#this file should be run evety time you want to start asemo on remote machine
#BUT you should run 1asemo-start.sh at least one time if you restart your router or change it

#launch asemo-robot file which will start roscore and teleop_twist_keyboard node
roslaunch asemo-robot.launch
