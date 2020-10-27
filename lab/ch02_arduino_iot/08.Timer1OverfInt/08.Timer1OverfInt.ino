int ledPin = 13;
void setup() {
  pinMode(ledPin, OUTPUT);  
  Serial.begin(9600);
  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
//  TCNT1 = 34286;    // 500ms Timer : preload timer 65536-16MHz/256/2Hz
  TCNT1 = 34286*2;    // 1sec Timer : preload timer 65536-16MHz/256/2Hz
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}
ISR(TIMER1_OVF_vect){ // interrupt service routine that wraps a user defined function supplied by attachInterrupt
  TCNT1 = 34286;            // 500ms preload timer
//  TCNT1 = 34286*32;            // 1sec preload timer
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
}
int cnt = 0;
void loop() {
  char buff[50]={0,};
  sprintf(buff, "Hello_%d!!", ++cnt);
  Serial.println(buff);
  delay(1000);
}
