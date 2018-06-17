/*
 * Arduino API JSON
 * 
 * This code was modified to obtain values used JSON for controlling an Arduino Braccio over a local network.
 * 
 * Modified by Yeshitha Amarasekara
 */

 /*
  Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
  M1=base degrees. Allowed values from 0 to 180 degrees
  M2=shoulder degrees. Allowed values from 15 to 165 degrees
  M3=elbow degrees. Allowed values from 0 to 180 degrees
  M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
  M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
  M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
  */

#include <Bridge.h>
#include <BridgeClient.h>
#include <ArduinoJson.h>
#include <Braccio.h>
#include <Servo.h>
#include <SPI.h>

BridgeClient client;
Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;

// Name address for Raspberry Pi
IPAddress ip(169, 254, 0, 2);
const char* server = "http://169.254.30.2:5000";

// Replace with your unique URL resource(Asking for the specific data)
const char* resource = "/command";

const unsigned long HTTP_TIMEOUT = 10000;  // Max respone time from server
const size_t MAX_CONTENT_SIZE = 512;       // Max size of the HTTP response

// The structure of data to be extracted from the JSON data
struct clientData {
  char delay_time[8];
  char M1[8];
  char M2[8];
  char M3[8];
  char M4[8];
  char M5[8];
  char M6[8];
};

// Initialization
void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  
  Serial.begin(115200);
  while(!Serial){
    //Waiting for Serial to start up
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);  
  }
  Bridge.begin();
}

// ARDUINO entry point #2: infinite loop
void loop() {

  client.stop();

  if(!client.connected()){
      client.connect(ip, 5000);
      if(client.connected()){
      
        Serial.print("Connected to the server at: ");
        Serial.println(ip);
    
        if(sendRequest(server, resource) && skipResponseHeaders()) {
          clientData clientData;
          if(readReponseContent(&clientData)) {
            // Run the desired function which requires the data
            Braccio_move(&clientData);
            wait();
          }  
      }
      else{
        Serial.println("Could not connect to server!");
      }
    }
    else{
      Serial.println("Already connected...");
      if(sendRequest(server, resource) && skipResponseHeaders()) {
        clientData clientData;
        if(readReponseContent(&clientData)) {
          // Run the desired function which requires the data
          Braccio_move(&clientData);
          wait();
        }      
      }
    }
  }

//void loop closes here
}


// Send the HTTP GET request to the server
bool sendRequest(const char* host, const char* resource) {

  client.print("GET ");
  client.print(resource);
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(host);
  client.println("Connection: close");
  client.println();

  return true;
}

// Skip HTTP headers so only handling the response data
bool skipResponseHeaders() {
  // HTTP headers end with an empty line
  char endOfHeaders[] = "\r\n\r\n";

  client.setTimeout(HTTP_TIMEOUT);
  bool ok = client.find(endOfHeaders);

  if (!ok) {
    Serial.println("No response or invalid response!");
  }
  
  return ok;
}

// Parse the JSON from the input string and extract the interesting values
bool readReponseContent(struct clientData* clientData) {
  // Compute the optimal size of the JSON buffer according on the data to be parsed
  // Computing the size on: https://bblanchon.github.io/ArduinoJson/assistant/
  const size_t bufferSize = JSON_OBJECT_SIZE(7) + 60;
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.parseObject(client);

  if (!root.success()) {
    return false;
  }

  // Copy the strings into the struct data from the JSONbuffer
  strcpy(clientData->delay_time, root["delay_time"]);
  strcpy(clientData->M1, root["M1"]);
  strcpy(clientData->M1, root["M2"]);
  strcpy(clientData->M3, root["M3"]);
  strcpy(clientData->M4, root["M4"]);
  strcpy(clientData->M5, root["M5"]);
  strcpy(clientData->M6, root["M6"]);

  return true;
}

// Run the function arduino braccio with the parsed data
void Braccio_move(const struct clientData* clientData) {
  int DT = atoi(clientData->delay_time);
  int Servo1 = atoi(clientData->delay_time);
  int Servo2 = atoi(clientData->delay_time);
  int Servo3 = atoi(clientData->delay_time);
  int Servo4 = atoi(clientData->delay_time);
  int Servo5 = atoi(clientData->delay_time);
  int Servo6 = atoi(clientData->delay_time);
  if(DT == 0){
    Serial.println("Data not modified!");
  }
  else {
    Braccio.ServoMovement(DT,Servo1,Servo2,Servo3,Servo4,Servo5,Servo6);  
  }
  //Check if the following delay is long enough for arm to move and recieve a new command
  delay(200);
}

// Pause for a one minute
void wait() {
  delay(5000);
  Serial.println();
}
