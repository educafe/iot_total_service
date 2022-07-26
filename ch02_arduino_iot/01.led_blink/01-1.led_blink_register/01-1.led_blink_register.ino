#include <avr/io.h>
#include <util/delay.h>

void setup() {
     Serial.begin(9600);
//    put your setup code here, to run once:
//    DDRB |= 1<<5;// Configuring PB5 as Output (pin 13)
    DDRB |= 1<<5;
//    DDRB = 0x20;
}

void loop() {
    // put your main code here, to run repeatedly:
    PORTB |= 1<<5; // Writing HIGH to PB5 (pin 13)
//    PORTB = 0x20;
    _delay_ms(1000); // Delay of 1 Second
//    PORTB &= ~(1<<5); // Writing LOW to PB5
    PORTB = 0x00;
    _delay_ms(1000); // Delay of 1 Second
}
