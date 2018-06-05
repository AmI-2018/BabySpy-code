#include <ArduinoJson.h>

const size_t MAX_CONTENT_SIZE = 512;

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

//Example of JSON data
//char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038}]"}

char json[] = "{\"delay_time\":20, \"M1\":360, \"M2\":360, \"M3\":360, \"M4\":360, \"M5\":360, \"M6\":360}";

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(9600);
  while (!Serial){
    //Waiting for the serial port to initialize
    digitalWrite(13, LOW);
    delay(500);
    digitalWrite(13, HIGH);    
  }
  clientData clientData;
  readReponseContent(&clientData);
  print_all(&clientData);
}

void loop() {
  // put your main code here, to run repeatedly:
}



bool readReponseContent(struct clientData* clientData) {
  // Compute the optimal size of the JSON buffer according on the data to be parsed
  // Computing the size on: https://bblanchon.github.io/ArduinoJson/assistant/
  const size_t bufferSize = JSON_OBJECT_SIZE(7) + 60;
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.parseObject(json);

  if (!root.success()) {
    Serial.println("JSON parsing failed, Stupid!");
    return false;
  }

  // Copy the strings into the struct data from the JSONbuffer
  strcpy(clientData->delay_time, root["delay_time"]);
  strcpy(clientData->M1, root["M1"]);
  strcpy(clientData->M2, root["M2"]);
  strcpy(clientData->M3, root["M3"]);
  strcpy(clientData->M4, root["M4"]);
  strcpy(clientData->M5, root["M5"]);
  strcpy(clientData->M6, root["M6"]);

  return true;
}

// Print the parsed data
void print_all(const struct clientData *clientData) {
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
