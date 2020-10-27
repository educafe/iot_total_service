/*
 *  Timer1 library example
 *  June 2008 | jesse dot tane at gmail dot com
 */
 
#include "TimerOne.h"
 
void setup()
{
      pinMode(10, OUTPUT);
      pinMode(8, OUTPUT);
      Timer1.initialize(250000);         // initialize timer1, and set a 1/2 second period
      Timer1.pwm(9, 64);                // setup pwm on pin 9, 50% duty cycle
      Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt
}
 
void callback()
{
    digitalWrite(10, digitalRead(10) ^ 1);
}
 
void loop()
{
    digitalWrite(8, HIGH);
    delay(1000);
    digitalWrite(8, LOW);
    delay(1000);
}
