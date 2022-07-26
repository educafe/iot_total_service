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
char btdata; // the data given from the computer

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
        btdata = bt.read(); //read from the serial connection
        switch(btdata){
          case '1': 
            delay(800);
            digitalWrite (LEDPin, HIGH); //if we get 1, turn on the LED
            bt.println("LED ON");
//            bt.write("\n");
            Serial.println(btdata);
            break;

          case '0' : //if we received 0, turn off the led
            delay(800);
            digitalWrite (LEDPin, LOW);
//            bt.println("LED OFF!!");
            bt.println("LED OFF");
            Serial.println(btdata);
            break;
        } 
    }
    delay (100); //prepare for data
}
