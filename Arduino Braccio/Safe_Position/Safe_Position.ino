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
//SERVO_DEGREE = (M1,M2,M3,M4,M5,M6)
//BASE = M1
//SHOULDER = M2
//ELBOW = M3
//VERTICAL WRIST = M4
//ROTATARY WRIST = M5
//GRIPPER = M6

//Code
void setup() {
                         //(step delay, M1, M2, M3, M4, M5, M6);
  Braccio.ServoMovement(20,           0,  15, 180, 170, 0,  73);  

  //Wait 1 second
  delay(1000);

  Braccio.ServoMovement(20,           180,  165, 0, 0, 180,  10);  

  //Wait 1 second
  delay(1000);

}

void loop() {
  //Braccio.ServoMovement(90,45,180,180,90,10);
}
