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
int timer=0;

void setup(){
    Serial.begin(9600);
    Serial.print("Sketch : "); Serial.println(__FILE__);
    bleSerial.begin(9600);
    bleSerial.print("AT+ROLE0");
    delay(5000);
    pinMode(LEDpin, OUTPUT);
    digitalWrite(LEDpin, LOW);
    // initialize timer1 
    noInterrupts();           // disable all interrupts
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0;

    OCR1A = 31250*2;    // 1sec Timer : compare match register 16MHz/256
    TCCR1B |= (1 << WGM12);   // CTC mode
    TCCR1B |= (1 << CS12);    // 256 prescaler 
    TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
    interrupts();             // enable all interrupts
}

ISR(TIMER1_COMPA_vect)  // timer compare interrupt service routine
{
    timer++;
}

void loop(){
    if(timer == 10){
         int chk = DHT.read11(DHT11_PIN);
        int temperature=DHT.temperature;
        int humidity=DHT.humidity;
        sprintf(buf1, "Temp:%dC, Hum:%d%%", temperature, humidity);
        bleSerial.write(buf1); 
        Serial.println(buf1);
        timer=0;
    }
    if (bleSerial.available()){
        c = bleSerial.read();
        Serial.println(c);
        if (c==49)   { 
            digitalWrite(LEDpin,HIGH);
        } 
        
        if (c==48) {
            digitalWrite(LEDpin,LOW);
        }
        bleSerial.flush();
    }
//    delay(3000);

}
