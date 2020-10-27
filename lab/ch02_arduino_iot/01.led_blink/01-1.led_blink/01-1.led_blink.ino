void setup() {
     Serial.begin(9600);
//    put your setup code here, to run once:
//    DDRB = 0x3F; // Using Hexadecimal Numbering System
    DDRB |= 1<<5;// Configuring PB5 as Output
//    PORTB = 0x3F; // Using Hexadecimal Numbering System
//    PORTB |= 1<<5;
}

void loop() {
    // put your main code here, to run repeatedly:
    PORTB |= 1<<5; // Writing HIGH to PB5
    _delay_ms(1000); // Delay of 1 Second
    PORTB &= ~(1<<5); // Writing LOW to PB5
    _delay_ms(1000); // Delay of 1 Second
}
