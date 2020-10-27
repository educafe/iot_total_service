int timer1 = 0;
int timer2 = 0;
int timer3 = 0;
int led=8;

void setup() {
    pinMode(12, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(8, OUTPUT);
    Serial.begin(9600);
    // initialize timer1
    noInterrupts();          // disable all interrupts
    TCCR0A = 0;             //Normal Mode -> incremental
    TCCR0B = 0;
    TCNT0  = 0;

    OCR0A = 255;      // 1sec Timer : compare match register 16MHz/256
    
    // CTC mode -> normal mode
    TCCR0A |= (1 << WGM01); 

    // 1024 prescaler together with CS02
    TCCR0B |= (1 << CS00);              // 1024 prescaler together with CS02
    TCCR0B |= (1 << CS02);              // 256 prescaler when used only
   
    // enable Timer/Counter0 Compare Match B
    TIMSK0 |= (1 << OCIE0B);           
   
    interrupts();                               // enable all interrupts
}

ISR(TIMER0_COMPB_vect) {
//    digitalWrite(led, digitalRead(led) ^ 1);          // toggle LED pin
//    Serial.println("TIMER0_COMPA interrupt");
    timer1++;
    timer2++;
    timer3++;
}

int cnt = 0;
void loop() {
    char buff[50] = {0,};
    if(timer1 == 100) {
        sprintf(buff, "timer1_%d!!", ++cnt);
        Serial.println(buff);
        digitalWrite(12, digitalRead(12) ^ 1);
        timer1 = 0;
    }

    if(timer2 == 200){
        sprintf(buff, "timer2_________%d!!", ++cnt);
        Serial.println(buff);
        digitalWrite(10, digitalRead(10) ^ 1);
        timer2 = 0;
    }

    if(timer3 == 30){
        sprintf(buff, "timer3___________________%d!!", ++cnt);
        Serial.println(buff);
        digitalWrite(8, digitalRead(8) ^ 1);
        timer3 = 0;
    }
//    delay(1000);
}

