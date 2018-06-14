/*
 * This sketch provides the Arduino with the capabilty to throw a ball.
 * 
 * Created by Yeshitha Amarasekara
 */

#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;


void setup() {
  Braccio.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
   * Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
   M1=base degrees. Allowed values from 0 to 180 degrees
   M2=shoulder degrees. Allowed values from 15 to 165 degrees
   M3=elbow degrees. Allowed values from 0 to 180 degrees
   M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
   M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
   M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
   */
  //Close at 70 and open at 10
  //Taking the ball
  Braccio.ServoMovement(0  ,60 ,15 ,90 ,90 ,90 ,10 );
  delay(5000);
  //Closing the hand 
  Braccio.ServoMovement(0  ,60 ,15 ,90 ,90 ,90 ,73 );
  delay(5000);
  //Throw the ball
  Braccio.ServoMovement(0  ,60 ,90 ,90 ,90 ,90 ,73 );
  delay(5000);
  
  
}
