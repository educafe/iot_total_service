int ledPin = 13;
int led2=11;
void setup() {
    pinMode(ledPin, OUTPUT);  
    pinMode(led2, OUTPUT);
    Serial.begin(9600);
    
    // initialize timer1 
    noInterrupts();           // disable all interrupts
    TCCR1A = 0;             // clear TCCR1A register
    TCCR1B = 0;             // clear TCCR1B register

    // 500ms Timer : preload timer 65536-16MHz/256/2Hz
    TCNT1 = 34286; 

    // 1sec Timer : preload timer 65536-16MHz/256
//    TCNT1 = 34286*2;
    
    // 256 prescaler 
    TCCR1B |= (1 << CS12);    
    
    // enable timer overflow interrupt
    TIMSK1 |= (1 << TOIE1);   
    
    interrupts();             // enable all interrupts
}

// interrupt service routine that wraps a user defined function supplied by attachInterrupt
ISR(TIMER1_OVF_vect){
    // 500ms preload timer
    TCNT1 = 34286;  

    // 1sec preload timer
//    TCNT1 = 34286*2; 
               
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
}

int cnt = 0;
void loop() {
    digitalWrite(led2, HIGH);
    delay(1000);
    digitalWrite(led2, LOW);
    delay(1000);
}
