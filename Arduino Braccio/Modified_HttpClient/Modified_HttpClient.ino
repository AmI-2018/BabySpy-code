/*
  Yún HTTP Client

 This example for the YunShield/Yún shows how create a basic
 HTTP client that connects to the internet and downloads
 content. In this case, you'll connect to the Arduino
 website and download a version of the logo as ASCII text.

 created by Tom igoe
 May 2013

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/HttpClient

 */

#include <Bridge.h>
#include <HttpClient.h>

void setup() {
  // Bridge takes about two seconds to start up
  // it can be helpful to use the on-board LED
  // as an indicator for when it has initialized
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  Serial.begin(115200);

  while (!Serial); // wait for a serial connection
}

void loop() {
  // Initialize the client library
  HttpClient client;
  Serial.println(1);

  // Make a HTTP request:
  client.get("http://169.254.0.2:5000/command");
  Serial.println(2);

  // if there are incoming bytes available
  // from the server, read them and print them:
  //while (client.available()) {
    Serial.println(3);
    char c = client.read();
    Serial.print(c);
    Serial.println(4);
  //}
  Serial.flush();

  delay(5000);
}
