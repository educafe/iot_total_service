// Basic bluetooth test sketch. HC-06_01
 
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX | TX
 
void setup(){
    Serial.begin(9600);
    BTSerial.begin(9600);
    Serial.print("Sketch : ");
    Serial.println(__FILE__);
    Serial.print("Uploaded : ");
    Serial.println(__DATE__);
    Serial.println("HM-06 is ready for AT commands:");
 
    // HC-06 default baud rate is 9600
    BTSerial.begin(9600);  
}
 
void loop(){
 
    // Keep reading from HC-06 and send to Arduino Serial Monitor
    if (BTSerial.available())
        Serial.println(BTSerial.readStringUntil('\n'));
//        Serial.println(BTSerial.read());
 
    // Keep reading from Arduino Serial Monitor and send to HC-06
    if (Serial.available())
        BTSerial.write(Serial.read());
//        BTSerial.println(Serial.read());
}
