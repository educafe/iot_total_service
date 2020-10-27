#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(5, 6); // RX, TX
char data;
 
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
}

void loop() // run over and over
{
  // Receive from Software Serial and send it to PC
  if (mySerial.available()) {
    Serial.print("Rx SW Serial -> ");
    Serial.write(mySerial.read());
    Serial.write('\n');
  }
 
  // Receive from PC and send it to Software Serial
  if (Serial.available()) {

#if 1
    mySerial.write(Serial.read());
#else
    data = Serial.read();
    mySerial.write(data);
    mySerial.write("\n");
#endif
    Serial.println("Write data to SW Serial...");
  }
}
