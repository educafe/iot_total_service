int led1 = 12;
int buzzer = 6;;
int key1 = 2;
int key2 = 3;
//interrupt_0 : pin2, interrupt_1 : pin3
void setup() {
    pinMode(key1, INPUT_PULLUP);
    pinMode(key2, INPUT_PULLUP);
    pinMode(led1, OUTPUT);
    pinMode(buzzer, OUTPUT);
    Serial.begin(9600);
    attachInterrupt(0, led1_toggle, FALLING);
    attachInterrupt(1, music_play, FALLING);
    digitalWrite(led1, LOW);
//    digitalWrite(buzzer, HIGH);
}

int fq[8] = {262, 294, 330, 349, 392, 440, 494, 523};
int song[26][2] = {
    {fq[4], 1}, {fq[4], 1}, {fq[5], 1}, {fq[5], 1},
    {fq[4], 1}, {fq[4], 1}, {fq[2], 2},
    {fq[4], 1}, {fq[4], 1}, {fq[2], 1}, {fq[2], 1}, 
    {fq[1], 3}, {0, 1},
    {fq[4], 1}, {fq[4], 1}, {fq[5], 1}, {fq[5], 1},
    {fq[4], 1}, {fq[4], 1}, {fq[2], 2},
    {fq[4], 1}, {fq[2], 1}, {fq[1], 1}, {fq[2], 1},
    {fq[0], 3}, {0, 1},
};

volatile int state1 = LOW;
volatile int state2 = LOW;
int cnt = 0;

void loop() {
    char buff[50];
    sprintf(buff, "Hello_%d!!", ++cnt);
    Serial.println(buff);
    delay(1000);
    if(state2==HIGH)
        music_start();
}

void led1_toggle() {  
    delayMicroseconds(2000);
    delay(2);
    if(digitalRead(key1) != LOW) return;
    state1 = !state1;
    digitalWrite(led1, state1); 
    Serial.println("key1 pressed"); 
//    digitalWrite(led1, not digitalRead(led1));
}
void music_play() {
    delayMicroseconds(2000);
    if(digitalRead(key2) != LOW) return;
    state2 = !state2;
    Serial.println("key2 pressed");
    for(int i=0; i<8; i++) {
        tone(buzzer, song[i][0], (song[i][1])*400);
        delay(song[i][1]*410);
   }
}
void music_start() {
    for(int i=0; i<26; i++) {
        tone(buzzer, song[i][0], (song[i][1])*333);
        delay(song[i][1]*334);
   }
}
