//Included Libraries
#include <Braccio.h>
#include <Servo.h>

//Variables
Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;

//Braccio.ServoMovement(SERVO_DEGREE); Controls the servo positions for each servo IN DEGREES.
//SERVO_DEGREE = (Movement Delay ,M1,M2,M3,M4,M5,M6)
//BASE = M1
//SHOULDER = M2
//ELBOW = M3
//VERTICAL WRIST = M4
//ROTATARY WRIST = M5
//GRIPPER = M6

//MIN DEGREE OF MOVEMENT 20 DEGREES

//Code
void setup() {
  Braccio.begin(); // Braccio Setup, moves the Servos to the safe position(20,  90,45,180,180,90,10)
}

void loop() {
  Braccio.ServoMovement(20,   80,90,30,90,0,75);   //Intial Position

  delay(250);
  //0,25,90,15,60,45
  Braccio.ServoMovement(20,   0,25,90,15,60,45);     //Final Position

  delay(250);
}
