void setup() {
    // put your setup code here, to run once:
    DDRB = 0x00;
    DDRB |= 1<<5;               // Configuring PB5 as Output pinMode(12, OUT)
    DDRB &= ~(1 << 1);      //Configuring PB0 as input, pinMode(10, IN)
    PORTB |=(0<<1);
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    uint8_t port_value = 0;
    port_value = PINB & (1<<1);          //digitalRead(10)
//    port_value = PINB;
    Serial.println(port_value, BIN);
   
    if ((port_value >> 1) == 1) // Reading the Pin Value
        {
            PORTB |= 1<<5; // Writing HIGH to glow LED, digitalWrite(12, HIGH)
        } 
        else
        {
            PORTB &= ~(1<<5); // Writing LOW, digitalWrite(12, LOW)
        }
        
    delay(1000);

}
