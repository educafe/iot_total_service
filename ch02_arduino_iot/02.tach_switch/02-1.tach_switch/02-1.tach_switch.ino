void setup() {
    // put your setup code here, to run once:
    DDRB = 0x00;
    DDRB |= 1<<5;                   // Configuring PB5 as Output pinMode(13 OUT)
    DDRD &= ~(1 << 2);              // Configuring PD2 as Input, pinMode(2, IN)
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    uint8_t port_value = 0;
    port_value = PIND & (1<<2);          //digitalRead(2)
//    port_value = PIND;
//    Serial.println(port_value>>2, BIN);
   
    if ((port_value >> 2) == 1){    // Reading the Pin Value
            PORTB |= 1<<5; // Writing HIGH to glow LED, digitalWrite(13, HIGH)
        } 
        else{
            PORTB &= ~(1<<5); // Writing LOW, digitalWrite(13, LOW)
        }
    delay(100);
}
