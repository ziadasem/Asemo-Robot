#export the commands to bash
#!/bin/bash

echo "#####################################"
echo "|||||||||||||||||||||||||||||||||||||"
echo ""
echo "Message from Asemo"
echo "Setting SSH for first time, Please type an easy password to remember" 
echo ""
echo ""
echo ""


#CONFIGURING HOSTS FILE; This file holds the ip address of the computers connected to RPI in the same network
# without configuring this file RPI can't connect to ROS environment

#  saving the remote ip address
read -p 'enter ip address of the remote computer, paste ip here ' uservar
#  saving ip address in ros environment
export ROS_MASTER_URI=http://$uservar:11311/

#  saving the remote machine name
read -p "add the remote computer name i.e pi-robot " pcName

#NOTE THIS FILE IS READ ONLY SO IF YOU RUN THIS SCRIPT FOR FIRST TIME USE $ sudo chmod 775 /etc/hosts
#adding the new device and its ip address to the file at the last line
echo $uservar  $pcName '#added by asemo-shell' >> /etc/hosts


#getting ip address for the local machine
ips=($(hostname -I))
for ip in "${ips[@]}"
do
    echo Your IP is  $ip 
done

#START SSH
# clearing previous ssh
ssh-keygen -f "/home/"$USER"/.ssh/known_hosts" -R $ip

# start SSh
ssh $ip

