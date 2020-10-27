//
//  What ever is entered in the serial monitor is sent to the connected device
//  Anything received from the connected device is copied to the serial monitor
//  Does not send line endings to the HM-10
//

 
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2,3); 
// https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html
 
 
char c=' ';
byte LEDpin = 13;
 
void setup() 
{
    Serial.begin(9600);
    Serial.print("Sketch:   ");   Serial.println(__FILE__);
    Serial.print("Uploaded: ");   Serial.println(__DATE__);
    Serial.println(" ");
 
    BTSerial.begin(9600);  
    Serial.println("BTserial started at 9600");
    Serial.println(" ");
 
    pinMode(LEDpin, OUTPUT); 
    digitalWrite(LEDpin,LOW); 

    // connect to the remote Bluetooth module
    BTSerial.print("AT+ROLE0");      //Slave advertise sending advertisement 
    delay(10000);
    pinMode(LEDpin, OUTPUT); 
    digitalWrite(LEDpin,LOW); 

}
 
void loop()
{
    // Read from the Bluetooth module and check if it is a command
    if (BTSerial.available())
    {
        c = BTSerial.read();
 
        // 49 is the ascii code for "1"
        // 48 is the ascii code for "0"
        if (c==49)   { 
            digitalWrite(LEDpin,HIGH);
            BTSerial.print("LED ON");   
        }
        if (c==48)   { 
            digitalWrite(LEDpin,LOW);   
            BTSerial.print("LED OFF");  
        }
        Serial.println(c);
        
    }
 
}
