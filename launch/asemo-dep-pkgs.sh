#export the commands to bash
#!/bin/bash

#This file configure the machine to get the required packages

echo please run this command as sudo

apt-get install openssh-server #for ssh
apt-get install ros-melodic-rosserial-arduino # for arduino
apt-get install ros-melodic-rosserial #for arduino
apt-get install ros-melodic-teleop-twist-keyboard #keyboard twist

