int led = 13;
int key = 2;
//interrupt_0 : pin2
int speed =1;
int blink=50;
long debounce = 2000;

void setup() {
    Serial.begin(9600);
    Serial.print("Sketch : ");
    Serial.println(__FILE__);
	pinMode(key, INPUT_PULLUP);
	pinMode(led, OUTPUT);
	attachInterrupt(0, led_toggle, FALLING);
	digitalWrite(led, LOW);
}

void loop() {
  digitalWrite(led, HIGH);
  delay(blink * speed);
  digitalWrite(led, LOW);
  delay(blink * speed);
}

void led_toggle() {
  delayMicroseconds(debounce);
   if(digitalRead(key) == LOW){
         speed = speed+1;
   }else{
        Serial.println("Spurious interrupt");
   }
  char buff[50];
  if(speed >= 21){
        speed = 1;
  }
  sprintf(buff, "Blink Speed is %d", speed*blink);
  Serial.println(buff);
}
