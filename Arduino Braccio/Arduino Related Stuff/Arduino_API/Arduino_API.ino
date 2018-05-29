/*
 * Arduino Braccio BabySpy API Sketch,
 * Written by Yeshitha Amarasekara
 * 
 * This sketch is for obtaining the name of the function to be called for the Arduino Braccio. 
 * The Raspberry Pi has to assign the URL to get the information from. This sketch provides one way
 * communication between the Raspberry Pi and the Arduino Yun.
 * 
 * NO SECURITY PROTOCAL, OR AUTHENTICATION unfortunately(Username and Password)
 */

 /*Decide what to do based on the filename; have functions for each string sent, or have
  * a randomize to mix parts of sketches, finally check if it's possible to open another
  * sketch based on this!(Switch Conditions for every case)
  */

//Libraries
#include <Bridge.h>  //Enables communication between the two chips of the Yun
#include <HttpClient.h>  //Library for the simplified API
//#include <randomized_functions_1.ino>  //Movements for the Arduino Braccio

//Definitions
#define MAX_ROW 20
#define MAX_COL 15
#define END 10//Set the value of the correct level in the MD array

//Variables
char data[MAX_ROW][MAX_COL]; //Array used for storage of the new URL
char url[MAX_ROW][MAX_COL];  //Fill each element with base URL
char URL[MAX_COL] = "www.url.com";
int OUTPUT_PIN = 13;
String key;
String flag;
String command;
int limit;
int i;
int g;

//Prototypes
String check_data();

void setup() {
  // Bridge connection takes about three seconds to start up hence the LED
  pinMode(LOW, OUTPUT_PIN);
  digitalWrite(OUTPUT_PIN, LOW);
  Bridge.begin();
  digitalWrite(OUTPUT_PIN, HIGH);
}

void loop() {
  HttpClient client;  // Initiate the Client variable and URL

  client.get(URL);  //Enter the URL or IP address for the Raspberry Pi
  
  while (client.available()){ //Check for new available incoming bytes
    for(i=0;i<MAX_ROW;i++){
      key = client.readStringUntil('/'); //Reads the string until the EOC
      key.toCharArray(data[i],255);
      //strcpy(data[i], key); //Enter the URL into a multidimensional array
    }
    
    command = check_data();
    
    //Braccio Functions:
    if(command == "Sketch1"){
      
    }
    else if(command == "Sketch2"){
      
    }
    else{
      
    }
    delay(250);  //Check and see if this delay is acceptable  
  }
}

String check_data(){
    for(g=0;g<MAX_COL;g++){
       if(data[END][g] = url[END][g]){
           flag = data[END][g]; //Enters the URL into a multidimensional array
       }
    }
  return flag;
}

