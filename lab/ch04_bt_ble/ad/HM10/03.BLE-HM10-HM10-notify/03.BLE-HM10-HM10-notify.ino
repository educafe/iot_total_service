/*
  This example code is in the public domain.
 */
#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3
SoftwareSerial bleSerial(rxPin, txPin); // RX, TX. For Leonardo, only pin 8, 9, 10, 11, 14, 15, 16 is can be used for rxPin.

char c=' ';
byte LEDpin = 13;

void setup()  
{
  Serial.begin(9600);
  Serial.print("Sketch : "); Serial.println(__FILE__);
//  pinMode (rxPin, INPUT);
//  pinMode (txPin, OUTPUT);

  bleSerial.begin(9600);
  // set slave
  bleSerial.print("AT+ROLE0");      //Slave advertise
  // or set master
  // bleSerial.print("AT+ROLE1");   //Master scan advertise and connect to
  delay(10000);

  pinMode(LEDpin, OUTPUT); 
  digitalWrite(LEDpin,LOW); 
}

void loop()
{
  if (bleSerial.available()){
    c = bleSerial.read();
 
        // 49 is the ascii code for "1"
        // 48 is the ascii code for "0"
        if (c==49)   { 
            digitalWrite(LEDpin,HIGH);
            bleSerial.write("LED ON");   
        }
        if (c==48)   { 
            digitalWrite(LEDpin,LOW);   
            bleSerial.write("LED OFF");  
        }
        Serial.println(c);  
  }
//    Serial.write(bleSerial.read());
  if (Serial.available())
    bleSerial.write(Serial.read());
}
