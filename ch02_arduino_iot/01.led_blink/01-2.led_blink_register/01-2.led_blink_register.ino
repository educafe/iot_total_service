#include <avr/io.h>
#include <util/delay.h>

void setup() {
     Serial.begin(9600);
//    put your setup code here, to run once:
//    DDRD |= 1<<5;// Configuring PD5 as Output (pin 5)
    DDRD |= 1<<5;
//    DDRD = 0x20;
}

void loop() {
    // put your main code here, to run repeatedly:
    PORTD |= 1<<5; // Writing HIGH to PD5 (pin 5)
//    PORTD = 0x20;
    _delay_ms(1000); // Delay of 1 Second
//    PORTD &= ~(1<<5); // Writing LOW to PD5
    PORTD = 0x00;
    _delay_ms(1000); // Delay of 1 Second
}
