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
char c;

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
        cmd=bt.readStringUntil('\n'); 
        Serial.println(cmd);
        if (cmd == "ON"){
          delay(800);
          bt.println("LED ON");
          digitalWrite(LEDPin, HIGH);
        } 
        else if (cmd == "OFF") {
          delay(800);
          bt.println("LED OFF");
          digitalWrite(LEDPin, LOW);
        }
    }
    delay (100); //prepare for data
}
