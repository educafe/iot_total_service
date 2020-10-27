#include <SoftwareSerial.h> //Serial library

SoftwareSerial ble (2,3);  //RX, TX (Switched on the Bluetooth - RX -> TX | TX -> RX)

int LEDPin = 13; //LED PIN on Arduino
int bledata; // the data given from the computer
int serdata;

void setup() {
    Serial.begin(9600);
    Serial.print("Sketch : "); Serial.println(__FILE__);
    ble.begin(9600); //Open the serial port
    pinMode (LEDPin, OUTPUT);
    Serial.println("Ready!!");
}

void loop() {
    if (ble.available()) { //if serial is available
        bledata = ble.read(); //read from the serial connection
        //Serial.println(bledata);
        Serial.write(bledata);
        Serial.println();
        if (bledata == '1') {
            digitalWrite (LEDPin, HIGH); //if we get 1, turn on the LED
            ble.println("LED ON!");  //write to serial->App에전송
        }   
        if (bledata == '0') { //if we received 0, turn off the led
            digitalWrite (LEDPin, LOW);
            ble.println ("LED OFF!");  //write to serial->App에전송
        }
    }
  
    if(Serial.available()){
        serdata = Serial.read();
        Serial.println(serdata);
//        ble.write(Serial.read());
        ble.write(serdata);
    }
    //  delay (100); //prepare for data
}
