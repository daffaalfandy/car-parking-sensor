/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial



#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX
#define ESP8266_BAUD 9600
ESP8266 wifi(&EspSerial);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "6txKaq4TTaRhkpNHDdR3hvENs4Yzp4Ke";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YUHUUU";
char pass[] = "inibukanwifi";

const int trigPin = 9; 
const int echoPin = 10;
const int speakerPin = 5;
int rangeVal;
float duration, distance; 

BLYNK_WRITE(V1) {
  rangeVal = param.asInt();
}

void setup()
{
  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 8080);

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(speakerPin, OUTPUT);

  
  
//  // Debug console
//  Serial.begin(9600);
//
//  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  
  Blynk.run();

  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH); 
  distance = (duration * 0.0343)/2; 
  digitalWrite(speakerPin, LOW);

  if(rangeVal > 0 ) {
    if (distance <= rangeVal) {
      digitalWrite(speakerPin, HIGH);
    }
  }
}
