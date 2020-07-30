#export the commands to bash
#!/bin/bash  

#Welcome Message
echo "#####################################"
echo "|||||||||||||||||||||||||||||||||||||"
echo ""
echo "Message from Asemo"
echo "Setting SSH for first time, Please type an easy password to remember" 
echo ""
echo ""
echo ""

#getting ip address for the local machine
ips=($(hostname -I))
for ip in "${ips[@]}"
do
    #print the local ip address to pass it as an argument in asemo shell file in RPi
    echo Your IP is  $ip please copy it in RPI bash file argument 
done

#START SSH
# clearing previous ssh
ssh-keygen -f "/home/"$USER"/.ssh/known_hosts" -R $ip

# starting ssh on local ip
ssh $ip

