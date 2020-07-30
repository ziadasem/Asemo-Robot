# Launch Asemo Shell files
for launching Asemo system you need to run multiple commmands on both machines, using the following commands make no need for run multiple commands or going through it

### Running the files
##### Install required packages
If you **run this file for the first time** you need to install some packages, instead of copying multiple commands run the following shell file which will install the required packages .
navigate to **launch directory** and run 
```sh
sudo ./asemo-dep-pkgs.sh
```

##### Setup ssh between the two devices
For connecting the data between two different devices or connecting data in ros environment this should done using the **secure shell protocol (ssh)**, for configuring ssh on both devices you should run multiple commands or just run this command. You should run it for one time only or when **you restart your router** or when **your IP address changes**
in the remote laptop run
```sh
./1asemo-start.sh
```
this file gets your ip address and start SSH .
Then on RPi run the following command to **configure RPi ssh**, You should run it for one time only or when **you restart your router** or when **your IP address changes**
```sh
./1asemo-start-rpi.sh
```
##### hosts file
When laptop connects to RPi and control it Rpi should record the ip and machine name of the remote computer. This is done in  the [hosts file](https://vitux.com/linux-hosts-file/). This script edits the host file and start ssh
##### Run the commands
This file runs every time you want to start Asemo system, the first file in remote laptop uses [roslaunch](http://wiki.ros.org/roslaunch) to start **roscore** and **teleop_twist_keyboard**
on your remote laptop run
```sh
./2asemo-start.sh
```

and on RPI run

```sh
./2asemo-start-rpi.sh
```
This script takes the ip of the remote computer to connect PRI to ROS environment and run [ros_serial](http://wiki.ros.org/rosserial)  package

### Breaking the code
#### asemo-dep-pkgs
This file run apt-get command to install required packages
```sh
apt-get install openssh-server #for ssh
apt-get install ros-melodic-rosserial-arduino # for arduino
apt-get install ros-melodic-rosserial #for arduino
apt-get install ros-melodic-teleop-twist-keyboard #keyboard twist
```

#### 1asemo-start and 1asemo-start-rpi
this file starts with number 1 means you should run before file 2
finding ip address 
```sh
ips=($(hostname -I))
for ip in "${ips[@]}"
do
    #print the local ip address to pass it as an argument in asemo shell file in RPi
    echo Your IP is  $ip please copy it in RPI bash file argument 
done
```
then passing to ssh to start
```sh
# clearing previous ssh
ssh-keygen -f "/home/"$USER"/.ssh/known_hosts" -R $ip
# starting ssh on local ip
ssh $ip
```

and for rpi the script add new machine name and ip address line to hosts file
```sh
#  saving the remote ip address
read -p 'enter ip address of the remote computer, paste ip here ' uservar
#  saving ip address in ros environment
export ROS_MASTER_URI=http://$uservar:11311/
#  saving the remote machine name
read -p "add the remote computer name i.e pi-robot " pcName
#NOTE THIS FILE IS READ ONLY SO IF YOU RUN THIS SCRIPT FOR FIRST TIME USE $ sudo chmod 775 /etc/hosts
#adding the new device and its ip address to the file at the last line
echo $uservar  $pcName '#added by asemo-shell' >> /etc/hosts
```
#### 2asemo-start
this file uses [roslaunch](http://wiki.ros.org/roslaunch) to launch teleop_twist_keyboard node
```sh
#launch asemo-robot file which will start roscore and teleop_twist_keyboard node
roslaunch asemo-robot.launch
```
#### asemo-robot launch
This launch file start teleop_twist_keyboard node and teleop_twist_keyboard.py executable
```xml
<node pkg="teleop_twist_keyboard" type="teleop_twist_keyboard.py" name="teleop_twist_keyboard" >
<remap from="/turtle1/cmd_vel" to="cmd_vel"/> <!--remapping the output of the twist_keyboard node to cmd_vel topic-->
</node>
```
#### 2asemo-start-rpi
This script takes the ip address of the remote computer to connect the rpi to ros environment
```sh
# reading ip address of the remote computer
read -p 'enter ip address of the remote computer, paste ip here ' uservar
#connecting to roscore in the remote computer
export ROS_MASTER_URI=http://$uservar:11311/
```
Then takes port number to start ros serial, if user didn't know the script will run *
```sh
read -p 'enter the serial port connected to arduino i.e (1,2 or 3) \n if you dont know remove all cables and let arduino serial cable only and type * '  number
if  [ -z "$number" ] # if user didn't type anything, i.e -z means isNull()
then
rosrun rosserial_python serial_node.py /dev/ttyACM*
else
rosrun rosserial_python serial_node.py /dev/ttyACM$number
fi #end if in shell
```

if the commands faild to run please connect to **[Muhammad Asem](https://github.com/Muhammad-asem)** or **[Ziad Asem](https://github.com/ziadasem)**
