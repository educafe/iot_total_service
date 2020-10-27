int ledPin = 10;
int key2 = 3;
int blink_rate=1;

void setup() {
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
    // initialize timer1
    noInterrupts();           // disable all interrupts
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0;

//    OCR1A = 31250/2;        // 250ms Timer: compare match register 16MHz/256/2Hz/2
    OCR1A = 31250;        // 500ms Timer: compare match register 16MHz/256/2Hz
//    OCR1A = 31250 * 2;      // 1sec Timer : compare match register 16MHz/256
    TCCR1B |= (1 << WGM12);           // CTC mode
    TCCR1B |= (1 << CS12);              // 256 prescaler
    TCCR1B |= (1 << CS10);              // for 1024 prescaler
#if 0
    TIMSK1 |= (1 << OCIE1A);           // enable Timer/Counter1 Compare Match A
#else
    TIMSK1 |= (1 << OCIE1B);           // enable Timer/Counter1 Compare Match B
#endif
    interrupts();                               // enable all interrupts

    pinMode(key2, INPUT_PULLUP);
    attachInterrupt(1, blink_rate_up, FALLING);
}

#if 0
ISR(TIMER1_COMPA_vect) {            // timer compare interrupt service routine
#else
ISR(TIMER1_COMPB_vect) {
#endif
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);          // toggle LED pin
}

int cnt = 0;
void loop() {
    char buff[50] = {0,};
    sprintf(buff, "Hello_%d!!", ++cnt);
    Serial.println(buff);
    delay(1000);
}

void blink_rate_up() {
    delay(1000);
    OCR1A = 31250/256*blink_rate++;
    char buff[50]={0,};
    sprintf(buff, "Blink_Rate : %d!!", blink_rate);
    Serial.println(buff);
//    Serial.println("Blink Rate Up : %d", blink_rate);
}
