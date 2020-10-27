#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(10, 11); // RX, TX
char value;
int LED=13;
void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
     ; // wait for serial port to connect. Needed for native USB port only
   }   
  Serial.println("Nice to meet you!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() // run over and over
{
  // Receive from Software Serial and send it to PC
  if (mySerial.available()) {
    Serial.print("Rx SW Serial -> ");
    value=mySerial.read();
    Serial.print(value);
    Serial.write('\n');
    switch(value) {
        case '1' :
            digitalWrite(LED,1);
            Serial.println("ON");
            mySerial.write("ON");
            mySerial.write("\n");
            break;
        case '0' :
            digitalWrite(LED,0);
            Serial.println("OFF");
            mySerial.write("OFF");
            mySerial.write("\n");
            break;
        default:
//            mySerial.write("*");
//            mySerial.write("\n");
            break;
    }
  }
  // Receive from PC and send it to Software Serial
  if (Serial.available()) {
    mySerial.write(Serial.read());
    Serial.println("Write data to SW Serial...");
  }
}
