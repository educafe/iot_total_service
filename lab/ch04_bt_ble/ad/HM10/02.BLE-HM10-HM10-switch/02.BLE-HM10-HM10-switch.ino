// HM-10_Example_01_simpleLED_Central
//
//  Simple remote control using HM-10s: LED on. LED off
//
//
//  Pins
//  BT VCC to Arduino 5V out. 
//  BT GND to GND
//  Arduino D8 (ASS RX) - BT TX no need voltage divider 
//  Arduino D9 (ASS TX) - BT RX through a voltage divider
//
 
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2,3); 
 
byte switchPin = 7;
boolean switch_State = LOW;
boolean oldswitch_State = LOW;
 
void setup() 
{
    Serial.begin(9600);
    Serial.print("Sketch: ");   Serial.println(__FILE__);
    Serial.print("Uploaded: ");   Serial.println(__DATE__);
    Serial.println(" ");
 
    BTSerial.begin(9600);  
    Serial.println("BTserial started at 9600");
    Serial.println(" ");
 
    pinMode(switchPin, INPUT_PULLUP); 
 
    // connect to the remote Bluetooth module
    BTSerial.print("AT+IMME1" );
    delay(1000);    
    BTSerial.print("AT+ROLE1" );
    delay(1000);
    BTSerial.print("AT+CON606405D14C00" );
    delay(1000);
 
}
 
void loop()
{
    // Very simple debouce.
    boolean state1 = digitalRead(switchPin); delay(1);
    boolean state2 = digitalRead(switchPin); delay(1);
    boolean state3 = digitalRead(switchPin); delay(1);
    if ((state1 == state2) && (state1==state3))  
    { 
        switch_State = state1;  
 
        if (switch_State != oldswitch_State)
        {
            if ( switch_State == HIGH) { 
                BTSerial.print("0" );  
                Serial.println("0"); 
            } else { 
                BTSerial.print("1" );  
                Serial.println("1"); 
            }
            oldswitch_State = switch_State;
        }
    }
}
