int timer1 = 0;
int timer2 = 0;
long timer3 = 0;
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
    
    TCCR0A = 0;             //Normal Mode -> incremental
    TCCR0B = 0;

     // 1024 prescaler
    TCCR0B |= (1 << CS00);             
    TCCR0B |= (1 << CS02); 
    
    TIMSK0 |= (1 << TOIE0);
    
    interrupts();                               // enable all interrupts
}

// timer compare interrupt service routine
ISR(TIMER0_OVF_vect) {           
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
        digitalWrite(led1, digitalRead(led1) ^ 1);
        timer1 = 0;
    }

    if(timer2 == 200){
        sprintf(buff, "timer2_________%d!!", ++cnt);
        Serial.println(buff);
        digitalWrite(led2, digitalRead(led2) ^ 1);
        timer2 = 0;
    }

    if(timer3 == 300){
        sprintf(buff, "timer3___________________%d!!", ++cnt);
        Serial.println(buff);
        digitalWrite(led3, digitalRead(led3) ^ 1);
        timer3 = 0;
    }
//    delay(1000);
}
