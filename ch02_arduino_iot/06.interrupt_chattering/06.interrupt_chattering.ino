int led = 13;
int key = 2;
//interrupt_0 : pin2
int speed =1;
int blink=100;
boolean state=false;
long debounce = 200;

void setup() {
    Serial.begin(9600);
    Serial.print("Sketch : ");
    Serial.println(__FILE__);
    Serial.print("Upload : ");
    Serial.println(__DATE__);
    
  pinMode(key, INPUT_PULLUP);
  pinMode(led, OUTPUT);
//  attachInterrupt(0, key_interrupt, FALLING);
  attachInterrupt(0, key_interrupt, RISING);
  digitalWrite(led, LOW);
}

void loop() {
  digitalWrite(led, HIGH);
  delay(blink * speed);
  digitalWrite(led, LOW);
  delay(blink * speed);
}

void key_interrupt() {
//    Serial.println("Interrupt----");
    delay(debounce);
//    if(digitalRead(key) == LOW)
    if(digitalRead(key) == HIGH)
       led_speed();
    else
        Serial.println("Spurious interrupt");
}

void led_speed(){
    speed=speed+1;
    char buf[30];
    sprintf(buf,"speed=%d", speed);
    Serial.println(buf);
}
