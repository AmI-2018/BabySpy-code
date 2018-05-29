/*
 * Arduino API JSON
 * 
 * This code was modified to obtain values used JSON for controlling an Arduino Braccio over a local network.
 * 
 * Modified by Yeshitha Amarasekara
 */

#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>

EthernetClient client;

// IP address for Raspberry Pi
//const char* server = "api.openweathermap.org";
const char* server = "127.0.0.1";

// Replace with your unique URL resource(Asking for the specific data)
const char* resource = ":5000/command1";

const unsigned long HTTP_TIMEOUT = 10000;  // Max respone time from server
const size_t MAX_CONTENT_SIZE = 512;       // Max size of the HTTP response

// Check if using a local network whether mac address is correct!
// Physical address (MAC): F4-30-B9-54-D6-F9
// byte mac[] = {0xF4, 0x30, 0xB9, 0x54, 0xD6, 0xF9};
byte mac[] = {0xB4, 0x21, 0x8A, 0xF8, 0x3C, 0x5F};


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
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to initialize
  }
  Serial.println("Serial ready");
  if(!Ethernet.begin(mac)) {
    Serial.println("Failed to configure Ethernet");
    return;
  }
  Serial.println("Ethernet ready");
  delay(1000);
}

// ARDUINO entry point #2: infinite loop
void loop() {
  if(connect(server)) {
    if(sendRequest(server, resource) && skipResponseHeaders()) {
      clientData clientData;
      if(readReponseContent(&clientData)) {
        // Run the desired function which requires the data
        printclientData(&clientData);
      }
    }
  }
  disconnect();
  wait();
}

// Opens the connection to the HTTP server
bool connect(const char* hostName) {
  Serial.print("Connect to ");
  Serial.println(hostName);

  bool ok = client.connect(hostName, 80);

  Serial.println(ok ? "Connected" : "Connection Failed!");
  return ok;
}

// Send the HTTP GET request to the server
bool sendRequest(const char* host, const char* resource) {
  Serial.print("GET ");
  Serial.println(resource);

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

// Run the function which required the parsed data
void printclientData(const struct clientData* clientData) {
  Serial.print("Delay time = ");
  Serial.println(clientData->delay_time);
  Serial.print("M1 = ");
  Serial.println(clientData->M1);
  Serial.print("M2 = ");
  Serial.println(clientData->M2);
  Serial.print("M3 = ");
  Serial.println(clientData->M3);
  Serial.print("M4 = ");
  Serial.println(clientData->M4);
  Serial.print("M5 = ");
  Serial.println(clientData->M5);
  Serial.print("M6 = ");
  Serial.println(clientData->M6);
}


// Close the connection with the HTTP server
void disconnect() {
  Serial.println("Disconnect");
  client.stop();
}

// Pause for a 1 minute
void wait() {
  Serial.println("Wait 60 seconds");
  delay(60000);
  Serial.println();
}

