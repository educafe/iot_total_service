int led = 12;
int key = 2;
//interrupt_0 : pin2
void setup() {
  pinMode(key, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(0, led_toggle, FALLING);
  digitalWrite(led, LOW);
}
volatile int state = LOW;
int cnt = 0;
void loop() {
  char buff[50]={0,};
  sprintf(buff, "Hello_%d!!", ++cnt);
  Serial.println(buff);
  delay(1000);
}
void led_toggle() {
  delayMicroseconds(2000);
  if(digitalRead(key) != LOW) return;
  state = !state;
  digitalWrite(led, state);
  
  Serial.println("Key1 pressed!!!");
  
}
