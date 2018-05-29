/*
 * Arduino API JSON
 * 
 * This code was modified to obtain values used JSON for controlling an Arduino Braccio over a local network.
 * 
 * Modified by Yeshitha Amarasekara
 */

#include <ArduinoJson.h>
#include <Ethernet.h>
#include <Braccio.h>
#include <Servo.h>
#include <SPI.h>

EthernetClient client;
Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;

// Name address for Raspberry Pi
const char* server = "api.openweathermap.org";

// Replace with your unique URL resource(Asking for the specific data)
const char* resource = "REPLACE_WITH_YOUR_URL_RESOURCE";

const unsigned long HTTP_TIMEOUT = 10000;  // Max respone time from server
const size_t MAX_CONTENT_SIZE = 512;       // Max size of the HTTP response

// Check if using a local network whether mac address is correct!
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

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
  Braccio.begin();
  if(!Ethernet.begin(mac)) {
    return;
  }
  delay(1000);
}

// ARDUINO entry point #2: infinite loop
void loop() {
  if(connect(server)) {
    if(sendRequest(server, resource) && skipResponseHeaders()) {
      clientData clientData;
      if(readReponseContent(&clientData)) {
        // Run the desired function which requires the data
        Braccio_move(&clientData);
      }
    }
  }
  disconnect();
  wait();
}

// Opens the connection to the HTTP server
bool connect(const char* hostName) {
  bool ok = client.connect(hostName, 80);
  return ok;
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
  }
  
  return ok;
}

// Parse the JSON from the input string and extract the interesting values
bool readReponseContent(struct clientData* clientData) {
  // Compute the optimal size of the JSON buffer according on the data to be parsed
  // Computing the size on: https://bblanchon.github.io/ArduinoJson/assistant/
  const size_t bufferSize = JSON_OBJECT_SIZE(3);
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.parseObject(client);

  if (!root.success()) {
    return false;
  }

  // Copy the strings into the struct data from the JSONbuffer
  strcpy(clientData->delay_time, root["main"]["delay_time"]);
  strcpy(clientData->M1, root["main"]["M1"]);
  strcpy(clientData->M1, root["main"]["M2"]);
  strcpy(clientData->M3, root["main"]["M3"]);
  strcpy(clientData->M4, root["main"]["M4"]);
  strcpy(clientData->M5, root["main"]["M5"]);
  strcpy(clientData->M6, root["main"]["M6"]);

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
  Braccio.ServoMovement(DT,Servo1,Servo2,Servo3,Servo4,Servo5,Servo6);
  //Check if the fllow delay is really neccessary
  delay(100);
}

// Close the connection with the HTTP server
void disconnect() {
  client.stop();
}

// Pause for a one minute
void wait() {
  delay(60000);
}
