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
  Braccio.begin();
}

void loop() {
    //Braccio.ServoMovement(90,45,180,180,90,10);
                         //(step delay, M1, M2, M3, M4, M5, M6);
  Braccio.ServoMovement(10,           90,  90, 90, 90, 90,  20);  

  //Wait 1 second
  delay(100);

  Braccio.ServoMovement(10,           90,  90, 90, 90, 90,  0);  

  //Wait 1 second
  delay(100);

}
