# Asemo Robot ROS Packages

This repository contain essential files for operating and developing Asemo, it contains :-

  - Ros packages for operating Asemo slam -written in C++ -
  - Arduino files - .ino- for moving and localizing Asemo
  - Simulation files for simulating Asemo
  - Configuration files for the ROS workspace and nodes

These packages are maintained by [Muhammad Asem](https://github.com/Muhammad-asem)  and   [ziad asem](https://github.com/ziadasem)
To install these packages run the following in your terminal

```sh
$ to be written 
```

or clone the repository in your computer by navigating to the directory you want to save the repo in and run the command in your terminal.
##### Note :- if you don't have git installed on your computer run the following command  `sudo apt install git`

```sh
$ git clone https://github.com/Muhammad-asem/Asemo-Robot
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

These packages contain their documentation 
