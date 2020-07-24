# Odom Publisher Node
This is c++ node code for odometry publisher node which subscribe data from **encoder** topic that conatins odometry data published from **[arduino node](../../Arduino/DC_ROS)** and publish the  [nav_msgs::Odometry](http://docs.ros.org/melodic/api/nav_msgs/html/msg/Odometry.html) **odom** that consists from [std_msgs/Header ](http://docs.ros.org/melodic/api/std_msgs/html/msg/Header.html) ,  [ geometry_msgs/PoseWithCovariance](http://docs.ros.org/melodic/api/geometry_msgs/html/msg/PoseWithCovariance.html), String and [geometry_msgs/TwistWithCovariance.msg](http://docs.ros.org/melodic/api/geometry_msgs/html/msg/TwistWithCovariance.html) to odom

### Subscribing from encoder topic
From the [arduino node documentation](../../Arduino/DC_ROS), When Asemo move its encoders publish its odometry to encoder topic. For every new message published to encoder topic the `encoder_cb()` function executed and calculate distance moved

```java
Dc=((2*3.14*R*(RtickNew-RtickOld)/N)+((2*3.14*R*(LtickNew-LtickOld)/N)))/2; //distance 
x+=Dc*cos(th);
y+=Dc*sin(th);
th+=((2*3.14*R*(RtickNew-RtickOld)/N)-((2*3.14*R*(LtickNew-LtickOld)/N)))/L; //angle 
```

### nav_msgs::Odometry 

##### Note: if you know this type of data type you can pass this section

The published data is in form of nav_msgs::Odometry then each nav_msgs::Odometry should contain the following data
* **Header**
    A header is a class held **standard metadata for higher-level stamped data types**. This is generally used to communicate timestamped data in a particular coordinate frame. The metadata are 
    * sequence id
    * time stamp
    * frame id
* **Child frame id**
  The child frame is assigned to relate twist with it, the main frame id is assigned in header.frame_id

* **PoseWithCovariance**
  From its name, its consists from pose ( *(x, y, z)* and *(x, y, z, w)* )  -i.e position and orientation - and Covariance 

* **TwistWithCovariance**
  Same for PoseWithCovariance consists from twist (linear and angular velocity) and Covariance

### Publishing to odom topic
The Published data is in form of **nav_msgs::Odometry** , PoseWithCovariance data are passed through the following code
```c
odom.pose.pose.position.x = x; //x is the distance calculated in encoder_cb
odom.pose.pose.position.y = y;
odom.pose.pose.position.z = 0.0; //Asemo can't move in this axis
```
And Covariance data from
    
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);
Where th is the theta calculated in encoder_cb and then passed to orientation
        
    odom.pose.pose.orientation = odom_quat;
And for twist data (TwistWithCovariance), we need to calculate velocity and time through the following code

First assign the current time to the new rostime object
```c
ros::Time current_time, last_time;
current_time = ros::Time::now();
last_time = ros::Time::now();
```
and then calculate the velocity
```c
double dt = (current_time - last_time).toSec();
vx=Dc*cos(th)/dt;
vy=Dc*sin(th)/dt;
```
then pass velocity to .twist
```c
odom.twist.twist.linear.x = vx;
odom.twist.twist.linear.y = vy;
odom.twist.twist.angular.z = vth;
```
Then pass the header data and child frame id
```c
odom.header.stamp = current_time;
odom.header.frame_id = "odom";
 odom.child_frame_id = "chassis";
```
At last pass the transform of Asemo through

```c
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "chassis";

    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;
    odom_broadcaster.sendTransform(odom_trans);
```




