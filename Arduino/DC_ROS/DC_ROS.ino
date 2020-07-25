 //INCLUSONS
 #include <ros.h>

 //include message types 
#include <geometry_msgs/Point32.h>
#include<geometry_msgs/Twist.h>

// --stepper definitons
#define TYPE DOUBLE
#define PI 3.14

//INCLUSONS of Adafruit library that simplify calculations
#include <AFMotor.h>
#include <Encoder.h>

//DEFINITIONS

//----- DC Motor definitions------------
AF_DCMotor motorL(4);  //left motor goes for pin 4
AF_DCMotor motorR(3);  //left motor goes for pin 3

//-------------Encoder definitions
Encoder R_enc(19, 18); //left motor encoder goes for pins 19 18
Encoder L_enc(21, 20); //left motor encoder goes for pins 21 20

long RoldPosition  = -999;
long LoldPosition  = -999;
 //-----------------------------------------Robot parameters definition------------ 
 #define L 0.33
 #define R 0.05
//--------------------------------Motors VARS-----------------------------------
// initializing variables
float vel=0.0; //as Twist msgs depend on Vector3 which is float64
float omega=0.0;
float VR,VL;
//-------------------pot vars---------
int i=0;


//-----------------------------------------------------------------------------------------
ros::NodeHandle  nh; //opreations on node instance

//------------------------------Publish init----------------------------------------------
geometry_msgs::Point32 Point_msg;
ros::Publisher enc_pub("/encoder", &Point_msg); //setup publisher to publish to '/encoder 'topic a pointer to point_msg

//-----------------------------------DC Motors Callback subscribers

//for every new Twist data published to cmd_vel topic this function is triggered and the new Twist is passed as 'msg'
void motors_cb(const geometry_msgs::Twist& msg)
{
 
 //twist message consistents from linear(x, y, z) and angular(x , y, z) velocity
 
    vel=msg.linear.x;    //init linear velocity (vel) to the linear velocity from twist data
    omega=msg.angular.z;  //init linear angular (omega) to the angular velocity from twist data
    
    // take care of it 
    VR=(2*vel+omega*L)/(2*R); // velocity for right wheel
    VL=(2*vel-omega*L)/(2*R); // velocity for left wheel
    //the negative sign in VL is to move the two wheels move in opposite direction, this will make Asemo move around its center
    
    
       motorR.run(FORWARD);  // move asemo forward if VR>0
       motorR.setSpeed(VR);  // move right wheel
      //---left---
      motorL.run(FORWARD);  // move asemo forward if VR>0
      motorL.setSpeed(VL);  // move left wheel
      
 //-------------negative part     
    if (VR<0)
    {
          motorR.run(BACKWARD);
          motorR.setSpeed(abs(VR));
          //----
    }
    if (VL<0){
          motorL.run(BACKWARD);
          motorL.setSpeed(abs(VL));
    }




}

//--------------------subscribers---------------------------
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", &motors_cb); 
// setup the subscriber to subscribe to '/cmd_vel' topic which publish geometry_msgs::Twist, for every new msg motors_cb will be triggered



 void setup() 
{
      Serial.begin (57600); //the baud rate for ros_serial package    
      //-----------------------------
       // turn on motor
      motorR.setSpeed(200);
      motorR.run(RELEASE);
     
      
      motorL.setSpeed(200);
      motorL.run(RELEASE);
      //---------------------------potintiometer ---------
      pinMode(A8,OUTPUT);
      pinMode(A10,INPUT);
      pinMode(A12,OUTPUT);
      digitalWrite(A8,HIGH);
      digitalWrite(A12,LOW);
      
      //---------------------------ROS Setup
      nh.advertise(enc_pub);  //publish to '/encoder topic*
      nh.subscribe(sub);      // subscribe to '/cmd_vel'
      }


 void loop() { 
      
   //----For right Encoder
     long RnewPosition = R_enc.read();
     if (RnewPosition != RoldPosition) {
          RoldPosition = RnewPosition;  //update positions
          Serial.println(RnewPosition);
        } 
        
  //----For left encoder
  long LnewPosition = L_enc.read();
  if (LnewPosition != LoldPosition) {
      LoldPosition = LnewPosition; //update positions
      Serial.println(LnewPosition);
      }  
//-------end of encoder

//--just for testing motors
//i=map(analogRead(A10),0,1023,0,255);
//i=78;
//Serial.println("Pot value:");
//Serial.println(i);

     /* motorR.run(FORWARD);
       motorR.setSpeed(i);
      //---left---
      motorL.run(FORWARD);
      motorL.setSpeed(i);
      */
      //----------


//-----------------------ROS publishing  
        Point_msg.x=RnewPosition;
        Point_msg.y=LnewPosition;
        enc_pub.publish(&Point_msg);
//-------------        
      nh.spinOnce(); //loop
      delay(10);
 }
