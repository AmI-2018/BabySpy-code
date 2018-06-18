/*
 * This sketch connects to an IP address on the network and retreives json data through
 * get request
 * 
 * Created by Yeshitha Amarasekara
 */


#include <BridgeClient.h>
#include <Bridge.h>
#include <ArduinoJson.h>
#include <SPI.h>

BridgeClient client;

// IP address for Raspberry Pi
IPAddress ip(169, 254, 0, 2);
const char* server = "http://169.254.0.2:5000";

// Replace with your unique URL resource(Asking for the specific data)
const char* resource = "/command";

const unsigned long HTTP_TIMEOUT = 20000;  // Max respone time from server
const size_t MAX_CONTENT_SIZE = 512;       // Max size of the HTTP response

// The structure of data to be extracted from the JSON data
typedef struct clientData {
  char delay_time[8];
  char M1[8];
  char M2[8];
  char M3[8];
  char M4[8];
  char M5[8];
  char M6[8];
}ClientData;

// Initialization
void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  digitalWrite(13, HIGH);
  Serial.begin(115200);
  Bridge.begin();
  digitalWrite(13, LOW);
  delay(2000);
}


void loop() {
  clientData* Data[20];
  client.stop();

  if(!client.connected()){
      client.connect(ip, 5000);
      if(client.connected()){
      
        Serial.print("Connected to the server at: ");
        Serial.println(ip);
    
        if(sendRequest(server, resource) && skipResponseHeaders()) {
          clientData clientData;
          if(readReponseContent(Data)) {
            // Run the desired function which requires the data
            print_all(Data);
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
        if(readReponseContent(Data)) {
          // Run the desired function which requires the data
          print_all(Data);
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
bool readReponseContent(ClientData** Data) {
  // Compute the optimal size of the JSON buffer according on the data to be parsed
  // Computing the size on: https://bblanchon.github.io/ArduinoJson/assistant/
  const size_t bufferSize = 7*JSON_ARRAY_SIZE(11) + JSON_OBJECT_SIZE(7) + 500;
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.parseObject(client);

  if (!root.success()) {
    Serial.println("JSON parsing failed!");
    return false;
  }

  int i;
  for(i=0; i<20 && strcmp(root["delay_time"][i], 0) != 0; i++){
    //Checck the NULL character before copying inside the terminating statement of for loop
    // Copy the strings into the struct data from the JSONbuffer
    strcpy(Data[i]->delay_time, root["delay_time"][i]);
    strcpy(Data[i]->M1, root["M1"][i]);
    strcpy(Data[i]->M1, root["M2"][i]);
    strcpy(Data[i]->M3, root["M3"][i]);
    strcpy(Data[i]->M4, root["M4"][i]);
    strcpy(Data[i]->M5, root["M5"][i]);
    strcpy(Data[i]->M6, root["M6"][i]); 
  }

  return true;
}

// Print the parsed data
void print_all(ClientData** Data) {
  int i;
  for(i=0;i<20;i++){
    Serial.print("For command Movement: ");
    Serial.println(i);
    Serial.print("Delay_time = ");
    Serial.println(Data[i]->delay_time);
    Serial.print("M1 = ");
    Serial.println(Data[i]->M1);
    Serial.print("M2 = ");
    Serial.println(Data[i]->M2);
    Serial.print("M3 = ");
    Serial.println(Data[i]->M3);
    Serial.print("M4 = ");
    Serial.println(Data[i]->M4);
    Serial.print("M5 = ");
    Serial.println(Data[i]->M5);
    Serial.print("M6 = ");
    Serial.println(Data[i]->M6);
    Serial.println();
    Serial.println();
    Serial.println();
  }
  /*int delay_time = atoi(Data->delay_time);
  if(delay_time == 0){
    Serial.println("Data not modified!");
  }
  else{
    Serial.print("Delay_time = ");
    Serial.println(Data->delay_time);
    Serial.print("M1 = ");
    Serial.println(Data->M1);
    Serial.print("M2 = ");
    Serial.println(Data->M2);
    Serial.print("M3 = ");
    Serial.println(Data->M3);
    Serial.print("M4 = ");
    Serial.println(Data->M4);
    Serial.print("M5 = ");
    Serial.println(Data->M5);
    Serial.print("M6 = ");
    Serial.println(Data->M6);
    Serial.println();
  }*/
}

// Pause for a one minute
void wait() {
  delay(5000);
  Serial.println();
}
