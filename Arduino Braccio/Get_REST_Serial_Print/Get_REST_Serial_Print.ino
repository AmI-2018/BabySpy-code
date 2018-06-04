/*
 * This sketch connects to an IP address on the network and retreives json data through
 * get request
 * 
 * Created by Yeshitha Amarasekara
 */


#include <Bridge.h>
#include <BridgeClient.h>
#include <ArduinoJson.h>
#include <SPI.h>

BridgeClient client;
boolean Connected;

// IP address for Raspberry Pi
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
  
  Serial.begin(9600);
  while(!Serial){
    //Waiting for Serial to start up
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);  
  }
  Bridge.begin();

  Connected = false;

  delay(200);
}


void loop() {
//New code must go in here
  if(!Connected){
    client.connect(ip, 5000);
    if(client.connected()){
      Serial.print("Connecting to the server at: ");
      Serial.println(ip);
      Serial.println("-1");
      Connected = true;
    }
    else{
      Serial.println("Could not connect to server!");
      Serial.println("-2");
      delay(5000);
    }
  }
  if(Connected){
    if(client.connected()){
      Serial.println("-3");
      //Really connected send real data, delay to prevent too much data streaming
      delay(20);
      //while (client.available()){
        Serial.println("-4");
        if(sendRequest(server, resource) && skipResponseHeaders()) {
          Serial.println("-5");
          clientData clientData;
          if(readReponseContent(&clientData)) {
            Serial.println("-6");
            // Run the desired function which requires the data
            print_all(&clientData);
          }
        }
        Serial.println("-7");
        wait();          
      //}
    }
  }
  else{
    Serial.println("Server connection closed!");
    Serial.println("End");
    client.stop();
    Serial.println();
    Connected = false;
  }

//void loop closes here
}

// Send the HTTP GET request to the server
bool sendRequest(const char* host, const char* resource) {

  client.print("GET ");
  client.print(resource);
  client.println(" HTTP/1.1");
  client.print("Host: ");
  //PROBLEM WITH THE HOST PARAMETER!!!!!
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
  const size_t bufferSize = JSON_OBJECT_SIZE(3);
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.parseObject(client);

  if (!root.success()) {
    Serial.println("JSON parsing failed!");
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

// Print the parsed data
void print_all(const struct clientData* clientData) {
  Serial.print("Delay_time = ");
  Serial.println(clientData->delay_time);
  Serial.print("M1 = ");
  Serial.println(clientData->M1);
  Serial.print("M2 = ");
  Serial.println(clientData->M1);
  Serial.print("M3 = ");
  Serial.println(clientData->M1);
  Serial.print("M4 = ");
  Serial.println(clientData->M1);
  Serial.print("M5 = ");
  Serial.println(clientData->M1);
  Serial.print("M6 = ");
  Serial.println(clientData->M1);
  Serial.println();
}

// Pause for a one minute
void wait() {
  delay(10000);
  Serial.println();
}
