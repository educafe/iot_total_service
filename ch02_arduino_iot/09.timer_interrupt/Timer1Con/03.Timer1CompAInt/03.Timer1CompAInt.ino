int ledPin = 13;
void setup() {
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
    
    // initialize timer1
    noInterrupts();              // disable all interrupts
    TCCR1A = 0;                 // clear TCCR1A register
    TCCR1B = 0;                 // clear TCCR1B register
    TCNT1  = 0;                  // clear Timer Counter1 counter register

    // 500ms Timer: compare match register 16MHz/256/2Hz
//    OCR1A = 31250;        
    
    // 1sec Timer : compare match register 16MHz/256
    OCR1A = 31250 * 2; 
    
    // Clear Timer on Compare match (CTC) mode     
    TCCR1B |= (1 << WGM12);   

    // 256 prescaler
    TCCR1B |= (1 << CS12);    

    // 64 prescaler
//    TCCR1B |= (1 << CS11); 
//    TCCR1B |= (1 << CS10); 

     // 8 prescaler
//    TCCR1B |= (1 << CS11); 

    // no prescaler
//    TCCR1B |= (1 << CS10); 

     // enable Timer/Counter1 Compare Match A
    TIMSK1 |= (1 << OCIE1A);
               
    interrupts();                               // enable all interrupts
}

// timer compare interrupt service routine
ISR(TIMER1_COMPA_vect) {            
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);  //LED on/off
}

int cnt = 0;
void loop() {
    char buff[50] = {0,};
    sprintf(buff, "Hello_%d!!", ++cnt);
    Serial.println(buff);
    delay(1000);
}

