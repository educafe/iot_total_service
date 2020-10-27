int buzzer = 6;;
int key1 = 2;
int key2 = 3;
volatile float musickey=1;
//interrupt_0 : pin2, interrupt_1 : pin3
void setup() {
    pinMode(key1, INPUT_PULLUP);
    pinMode(key2, INPUT_PULLUP);
    pinMode(buzzer, OUTPUT);
    Serial.begin(9600);
    attachInterrupt(0, key_down, FALLING);
    attachInterrupt(1, key_up, FALLING);
//  digitalWrite(buzzer, HIGH);
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
//  if(state2==HIGH)
    music_start();
}
void key_down() { 
    delayMicroseconds(3000);
    if(digitalRead(key1) != LOW) return; 
    Serial.println("key1 pressed"); 
    musickey=musickey/2;
}
void key_up() {
    delayMicroseconds(3000);
    if(digitalRead(key2) != LOW) return; 
    Serial.println("key2 pressed");
    musickey=musickey*2;
}
void music_start() {
  for(int i=0; i<26; i++) {
      tone(buzzer, song[i][0]*musickey, (song[i][1])*333);
      delay(song[i][1]*334);
   }
}
