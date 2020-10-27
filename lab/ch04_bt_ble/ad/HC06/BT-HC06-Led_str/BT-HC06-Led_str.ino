//This sketch shows how to connect to a bluetooth device
// Arduino -> bluetooth
// Used with Android BlueTerm app

#include <SoftwareSerial.h> //Serial library

/**
 * Arduino connection HC-06 connection: 
 * HC-06  | Arduino
 * TX     | 2
 * RX     | 3
*/
// Here, we exchange them -
SoftwareSerial bt (2,3);  //RX, TX (Switched on the Bluetooth - RX -> TX | TX -> RX)
int LEDPin = 13; //LED PIN on Arduino
//char btdata; // the data given from the computer
String cmd="";
String result="";

void setup() {
    Serial.begin(9600);
    bt.begin(9600); //Open the serial port
    Serial.println ("Bluetooth ON. Press 1 or 0 to blink LED.."); //write to serial->App에전송
    pinMode (LEDPin, OUTPUT);
    Serial.println(__FILE__);
}

void loop() {
    //  delay (100); //prepare for data
    if (bt.available()) { //if serial is available
//        cmd=bt.readStringUntil('\n');
        cmd=bt.readStringUntil('\n'); 
        if (cmd == "ON"){
          delay(800);
          Serial.println(cmd);
          digitalWrite(LEDPin, HIGH);
          result="LED ON";
          bt.println(result);
        } 
        else if (cmd == "OFF") {
          delay(800);
          digitalWrite(LEDPin, LOW);
          Serial.println(cmd);
          result="LED OFF";
          bt.println(result);
        }
    }
    delay (100); //prepare for data
}
