// Basic bluetooth test sketch. HC-06_01
 
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX | TX
 
void setup(){
    Serial.begin(9600);
    Serial.print("Sketch : ");
    Serial.println(__FILE__);
    Serial.print("Uploaded : ");
    Serial.println(__DATE__);
    Serial.println("HM-10 is ready for AT commands:");
    Serial.println("For HM-10 (HS0019) module, AT command shall be given in small char!!!");
    Serial.println("On monitor, the setting shall be both NL&CR!!!");

    // HC-06 default baud rate is 9600
    BTSerial.begin(9600);  
}
 
void loop(){
 
    // Keep reading from HC-06 and send to Arduino Serial Monitor
    if (BTSerial.available())
        Serial.write(BTSerial.read());
//        Serial.println(BTSerial.read());
 
    // Keep reading from Arduino Serial Monitor and send to HC-06
    if (Serial.available())
        BTSerial.write(Serial.read());
//        BTSerial.println(Serial.read());
}
