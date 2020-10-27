int ledPin = 8;
int led2=7;
void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(led2, OUTPUT);
    Serial.begin(9600);
    // initialize timer1
    noInterrupts();           // disable all interrupts
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0;

     // 500ms Timer: compare match register 16MHz/256/2Hz
    OCR1A = 31250;        
    
    // 1sec Timer : compare match register 16MHz/256
//    OCR1A = 31250 * 2; 
    
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

    // enable Timer/Counter1 Compare Match B
    TIMSK1 |= (1 << OCIE1B);    
           
    interrupts();                               // enable all interrupts
}

ISR(TIMER1_COMPB_vect) {
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);          // toggle LED pin
}

int cnt = 0;
void loop() {
   digitalWrite(led2, HIGH);
   delay(1000);
   digitalWrite(led2, LOW);
   delay(1000);
}

