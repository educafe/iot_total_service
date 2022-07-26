int red = 13;
int yellow = 9;
int green = 7;
int key = 2;
//interrupt_0 : pin2
int speed =1;
int blink=100;

void setup() {
    Serial.begin(9600);
    Serial.print("Sketch : ");
    Serial.println(__FILE__);
	pinMode(key, INPUT_PULLUP);
	pinMode(red, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);
	attachInterrupt(0, led_toggle, FALLING);
	digitalWrite(red, LOW);
}

void loop() {
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
    delay(blink * speed);
    digitalWrite(red, LOW);
    digitalWrite(yellow, HIGH);
    delay(blink * speed);
    digitalWrite(yellow, LOW);
    digitalWrite(green, HIGH);
    delay(blink * speed);
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    delay(blink * speed);
}

void led_toggle() {
    delay(100);
    if(digitalRead(key) == LOW){
    char buff[50];
    speed = speed+1;
    if(speed >= 11){
        speed = 1;
    }
    sprintf(buff, "Blink Speed is %d", speed*blink);
    Serial.println(buff);
    }
}
