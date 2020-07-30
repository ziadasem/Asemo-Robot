# Asemo Robot ROS Packages

This repository contain essential files for operating and developing Asemo, it contains :-

  - Ros packages for operating Asemo slam -written in C++ -
  - Arduino files - .ino- for moving and localizing Asemo
  - Simulation files for simulating Asemo
  - Configuration files for the ROS workspace and nodes

These packages are created by [Muhammad Asem](https://github.com/Muhammad-asem) and maintained by [Muhammad Asem](https://github.com/Muhammad-asem) and [Ziad Asem](https://github.com/ziadasem)   
To install these packages run the following in your terminal

```sh
$ to be written 
```

or clone the repository in your computer by navigating to the directory you want to **save the repository** in and run the command in your terminal.
##### Note :- if you don't have git installed on your computer run the following command  `sudo apt install git`


```sh
$ git clone https://github.com/Muhammad-asem/Asemo-Robot
```
and on RPi run 
```sh
wget  https://raw.github.com/Muhammad-asem/Asemo-Robot/launch/1asemo-start-rpi.sh
wget  https://raw.github.com/Muhammad-asem/Asemo-Robot/launch/2asemo-start-rpi.sh
wget  https://raw.github.com/Muhammad-asem/Asemo-Robot/launch/asemo-dep-pkgs.sh
```

The packages in this repository are listed below - each package has its own documentation in its directory-
1. Arduino package
    This package contains arduino files -.ino- for moving the robot and publish the odometry and encoder file
1. Gazebo package
     Gazebo is a set of packages that provide the necessary interfaces to simulate a robot, this package contain all the data to simulate Asemo 

1. Joint states subscriber package
   this package for Arm robot not for Asemo

1. Mybot description package
   this package is describing the robot mechanically  **Not sure**

1. Mybot nav package
   this package contains all launch files for Asemo

1. Odom pub package
   this package subscribe the odometry data from the encoder arduino

### Running ASEMO system
Full documentation for the commands in the **launch directory**, if you use Asemo system for the first time you need to install required packages by navigating to launch directory and run the scripts .
```sh
cd launch
sudo chmod 777 asemo-dep-pkgs.sh
sudo chmod 777 1asemo-start.sh
sudo chmod 777 2asemo-start.sh
sudo chmod 777 1asemo-start-rpi.sh
sudo chmod 777 2asemo-start-rpi.sh
./asemo-dep-pkgs.sh
```
this will install all the required packages.

Then on your remote laptop run the following command, You should run it for one time only or when **you restart your router** or when **your IP address changes** . This will start ssh type an easy password to remember
```sh
./1asemo-start.sh
```

Then on rpi run this command and rerun it when the previous conditions occur
```sh
./1asemo-start-rpi.sh
```
launch the node on remote computer by typing the following command
```sh
/2asemo-start.sh
```
and on RPi
```sh
/2asemo-start-rpi.sh
```
write the ip address of the remote computer to connect the rpi to ros environment

### ASEMO ROS System
Asemo SLAM consists of motor drivers for moving and kinect for observing the environment (see the [schematic](https://ibb.co/2FccxP3)). For moving the robot, the remote laptop **is connected** to RPI and move Asemo through keyboard stroke, the keyboard stroke is published to **cmd_ve**l topic **not turtle1/cmd_vel** then the arduino node subscribe this topic and publish odometry to **encoder topic** then **odometry_publisher** node subscribe on this node and publish to **odom topic**
