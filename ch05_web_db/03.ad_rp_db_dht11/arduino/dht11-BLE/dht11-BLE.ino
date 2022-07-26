#include <dht.h>
#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3
#define DHT11_PIN 8

SoftwareSerial bleSerial(2,3);
dht DHT;
byte LEDpin=13;
char c=' ';
char buf1[18];
char buf2[28];

void setup(){
    Serial.begin(9600);
    Serial.print("Sketch : "); Serial.println(__FILE__);
    bleSerial.begin(9600);
    bleSerial.print("AT+ROLE0");
    delay(5000);
    pinMode(LEDpin, OUTPUT);
    digitalWrite(LEDpin, LOW);
    pinMode(7, OUTPUT);
}

void loop(){
    int chk = DHT.read11(DHT11_PIN);
    int temperature=DHT.temperature;
    int humidity=DHT.humidity;
    sprintf(buf1, "Temp:%dC, Hum:%d%%", temperature, humidity);
    bleSerial.write(buf1); 
    Serial.println(buf1);
    if (bleSerial.available()){
        c = bleSerial.read();
        Serial.println(c);
        if (c==49)   { 
            digitalWrite(LEDpin,HIGH);
            delay(100);
            digitalWrite(LEDpin,LOW);
        }
        bleSerial.flush();
    }
    delay(3000);

}
