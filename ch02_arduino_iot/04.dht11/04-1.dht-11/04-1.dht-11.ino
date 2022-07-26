#include <dht.h>    //DHTLib.zip

#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3
#define DHT11_PIN 8
dht  myDHT;
char buf[18];

void setup(){
  Serial.begin(9600);
  Serial.println(__FILE__);
}

void loop()
{
    int chk = myDHT.read11(DHT11_PIN);
    int temperature=myDHT.temperature;
    int humidity=myDHT.humidity;
    sprintf(buf, "Temp:%dC, Hum:%d%%", temperature, humidity);
    Serial.println(buf);
    delay(2000);

}
