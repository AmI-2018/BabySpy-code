/* API Client Code

  This sketch allows the Yun to connect to a local http and receive a text file containin the code from the API
  you would like to run.

  This is a modifed sketch from Yun Client available in the Arduino Libraries.

  Modified by Yeshitha Amarasekara

 */

//Libraries
#include <Bridge.h>
#include <Braccio.h>
#include <Servo.h>
#include <HttpClient.h>
#include <SPI.h>
#include <SD.h>

//Variables
File file;
char c;
Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;


void setup() {
  // Bridge takes about two seconds to start up
  // it can be helpful to use the on-board LED
  // as an indicator for when it has initialized
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  Braccio.begin();
  digitalWrite(13, HIGH);

  Serial.begin(9600);
  while (!Serial){
  }
}

void loop() {
  // Initialize the client library
  HttpClient client;

  // Make a HTTP request:
  // Enter the Local URL on the network from where to download the file
  // Initializing the file
  client.get("");
  file = SD.open("code.ino", FILE_WRITE);

  if(!SD.begin(4)){
    Serial.println("Initialization Failed!");
  }
  
  // If there are incoming bytes available
  // From the server, read them and print them:
  while (client.available()) {
    c = client.read();

    if (file){
      if(c != ';'){
        file.print(c);        
      }
      else{
        file.println();
      }
    }
    file.close();

  //Running the code that was just received.
  //The main structure of the code alwasys has to start with void start(){ and end with }
  start();
  
  //Delay before checking for new data
  delay(5000);
  }
}


