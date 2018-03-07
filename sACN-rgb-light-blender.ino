/*
   sACN RGB Light Blender


   Rosco Micro C4 channels at ITP:
   251 - red
   252 - green
   253 - blue

  Built with 
  -[Tom Igoe's sACN Intro example (created 17 Jan 2018, updated 19 Feb 2018)](https://github.com/tigoe/sACNSource/blob/master/examples/sACNIntro/sACNIntro.ino)
  -[Adafruit FSR Example](https://learn.adafruit.com/force-sensitive-resistor-fsr/using-an-fsr)



*/

//WIFI & DMX Libraries
#include <SPI.h>
#include <WiFi101.h>
//#include <ESP8266WiFi.h>    // This should work with the ESP8266 as well.
#include <WiFiUdp.h>
#include <sACNSource.h>
#include "arduino_secrets.h" 

WiFiUDP Udp;                                  // instance of UDP library
sACNSource myController(Udp);                 // Your Ethernet-to-DMX device
char receiverAddress[] = "";      // sACN receiver address

int myUniverse = 1;                                 // DMX universe
char myDevice[] = "";                   // sender name
char myUuid[] = ""; // sender UUID


// PAD and Feedback LED PINS
int rPAD = A3; // Red Pad Connected to A3
int gPAD = A2; // Green Pad Connected to A2
int bPAD = A1; // Blue Pad Connected to A1

//RGB LED light & DMX Channels of RoscoMICRO C4
int rLED = 5;      // connect RED LED leg to pin 5 (PWM pin)
// Insert RED Channel Variable here (251)
int gLED = 4;      // connect GREEN LED leg to pin 4 (PWM pin)
// Insert GREEN Channel Variable here (252)
int bLED = 3;      // connect BLUE LED leg to pin 3 (PWM pin)
// Insert BLUE Channel Variable here (253)



// Velostat values when circuits are closed
int rPADval; //FSR reading for RED pad
int gPADval; //FSR reading for GREEN pad
int bPADval; //FSR reading for BLUE pad

//Brightness of LEDs
int rLEDint; // RED LED brightness
int gLEDint; // GREEN LED brightness
int bLEDint; // BLUE LED brightness



void setup() {
  Serial.begin(9600);
  //  while you're not connected to a WiFi AP,
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: aaronlights");
    Serial.println(SECRET_SSID);           // print the network name (SSID)
    WiFi.begin(SECRET_SSID, SECRET_PASS);     // try to connect
    delay(2000);
  }
  // initialize sACN source:
  myController.begin(myDevice, myUuid, myUniverse);

  // When you're connected, print out the device's network status:
  IPAddress ip = WiFi.localIP();
  Serial.println("Connection successful");
  Serial.println("IP Address: ");
  Serial.println(ip);


  // set DMX channel values to 0:
  for (int dmxChannel = 1; dmxChannel < 513; dmxChannel++) {
    myController.setChannel(dmxChannel, 0);
  }
  myController.sendPacket(receiverAddress);
  // set green and blue channels to make a teal hue:
  //R
  myController.setChannel(251, 0);  
  //G
  myController.setChannel(252, 0);
  //B
  myController.setChannel(253, 0);

  pinMode(rLED, OUTPUT);
  pinMode(gLED, OUTPUT);
  pinMode(bLED, OUTPUT);
 
  

}

void loop() {

  // here's where the action happens

  // RED pad reading
        rPADval = analogRead(rPAD);
        
        if (rPADval>20){
        Serial.print("Red PAD Value is = ");
        Serial.println(rPADval);
        }
        
        // map FSR values (0-1023) to RGB Values (0-255)
        rLEDint = map(rPADval, 0, 1023, 0, 255);
        analogWrite(rLED, rLEDint);
        

        myController.setChannel(251, rLEDint);
        Serial.println(rLEDint);
        myController.sendPacket(receiverAddress);      
        delay(100);


  delay(500);

    // GREEN pad reading
        gPADval = analogRead(gPAD);
        
        if (gPADval>20){
        Serial.print("Green PAD Value is = ");
        Serial.println(gPADval);
        }
        
        // map FSR values (0-1023) to RGB Values (0-255)
        gLEDint = map(gPADval, 0, 1023, 0, 255);
        analogWrite(gLED, gLEDint);
        

        myController.setChannel(252, gLEDint);
        Serial.println(gLEDint);
        myController.sendPacket(receiverAddress);      
        delay(100);


  delay(500);

      // BLUE pad reading
        bPADval = analogRead(bPAD);
        
        if (bPADval>20){
        Serial.print("BLUE PAD Value is = ");
        Serial.println(bPADval);
        }
        
        // map FSR values (0-1023) to RGB Values (0-255)
        bLEDint = map(bPADval, 0, 1023, 0, 255);
        analogWrite(bLED, bLEDint);
        

        myController.setChannel(253, bLEDint);
        Serial.println(bLEDint);
        myController.sendPacket(receiverAddress);      
        delay(100);


  delay(500);

}
