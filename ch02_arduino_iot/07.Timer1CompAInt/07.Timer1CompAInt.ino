int ledPin = 13;
void setup() {
      pinMode(ledPin, OUTPUT);  
      Serial.begin(9600);
      // initialize timer1 
      noInterrupts();           // disable all interrupts
      TCCR1A = 0;
      TCCR1B = 0;
      TCNT1  = 0;
    
//      OCR1A = 31250;    // 500ms Timer: compare match register 16MHz/256/2Hz
      OCR1A = 31250*2;    // 1sec Timer : compare match register 16MHz/256
      TCCR1B |= (1 << WGM12);   // CTC mode
      TCCR1B |= (1 << CS12);    // 256 prescaler 
      TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
      interrupts();             // enable all interrupts
}
ISR(TIMER1_COMPA_vect)  // timer compare interrupt service routine
{
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);   // toggle LED pin
}
int cnt = 0;
void loop() {

}
