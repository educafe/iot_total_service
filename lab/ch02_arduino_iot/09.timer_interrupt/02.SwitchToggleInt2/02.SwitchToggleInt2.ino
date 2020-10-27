int led1 = 12;
int led2 = 10;;
int key1 = 2;
int key2 = 3;
//interrupt_0 : pin2, interrupt_1 : pin3
void setup() {
    pinMode(key1, INPUT_PULLUP);
    pinMode(key2, INPUT_PULLUP);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    Serial.begin(9600);
    attachInterrupt(0, led1_toggle, FALLING);
    attachInterrupt(1, led2_toggle, FALLING);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
}
volatile int state1 = LOW;
volatile int state2 = LOW;
int cnt = 0;
void loop() {
    char buff[50];
    sprintf(buff, "Hello_%d!!", ++cnt);
    Serial.println(buff);
    delay(1000);
}
void led1_toggle() {  
    delayMicroseconds(2000);
    if(digitalRead(key1) != LOW) return;
  state1 = !state1;
  digitalWrite(led1, state1);  
    Serial.println("Key1 pressed!!!");
}
void led2_toggle() {
    delayMicroseconds(2000);
    if(digitalRead(key2) != LOW) return;
//      state2 = !state2;
//      digitalWrite(led2, state2);
    digitalWrite(led2, not digitalRead(led2));
    Serial.println("Key2 pressed!!!");
}
