int timer1 = 0;
int timer2 = 0;
int timer3 = 0;
int led1=13;
int led2=11;
int led3=9;

void setup() {
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    Serial.begin(9600);
    // initialize timer1
    noInterrupts();          // disable all interrupts
    TCCR2A = 0;             //Normal Mode -> incremental
    TCCR2B = 0;
    TCNT2  = 0;
    TCNT0 = 0;

    TCCR0A = 0;             //Normal Mode -> incremental
    TCCR0B = 0;
    TCNT0  = 0;

    OCR2A = 255;      // 1sec Timer : compare match register 16MHz/256
    TCCR2A |= (1 << WGM21);           // CTC mode -> normal mode
    TCCR2B |= (1 << CS00);              
    TCCR2B |= (1 << CS01);   
    TCCR2B |= (1 << CS02); 
//    TIMSK2 |= (1 << OCIE2A);           // enable Timer/Counter0 Compare Match A

    OCR0A = 255;      // 1sec Timer : compare match register 16MHz/256
    TCCR0B |= (1 << WGM12);           // CTC mode -> normal mode
//    TCCR0B |= (1 << CS00);              // 
//    TCCR0B |= (1 << CS01);   
    TCCR0B |= (1 << CS02); 
    TIMSK0 |= (1 << OCIE0A);           // enable Timer/Counter0 Compare Match A
    
    interrupts();                               // enable all interrupts
}

#if 0
ISR(TIMER2_COMPA_vect) {            // timer compare interrupt service routine
//    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);          // toggle LED pin
//    Serial.println("TIMER2_COMPA interrupt");
    timer1++;
    timer2++;
    timer3++;
}

#else

ISR(TIMER0_COMPA_vect) {            // timer compare interrupt service routine
//    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);          // toggle LED pin
//    Serial.println("TIMER0_COMPA interrupt");
    timer1++;
    timer2++;
    timer3++;
}

#endif

int cnt = 0;
void loop() {
    char buff[50] = {0,};
    if(timer1 == 250) {
        timer1 = 0;
        sprintf(buff, "timer1_%d!!", ++cnt);
        Serial.println(buff);
        digitalWrite(led1, digitalRead(led1) ^ 1);
    }

    if(timer2 == 500){
        timer2 = 0;
        sprintf(buff, "timer2_________%d!!", ++cnt);
        Serial.println(buff);
        digitalWrite(led2, digitalRead(led2) ^ 1);
    }

    if(timer3 == 300){
        timer3 = 0;
        sprintf(buff, "timer3___________________%d!!", ++cnt);
        Serial.println(buff);
        digitalWrite(led3, digitalRead(led3) ^ 1);
    }
}
