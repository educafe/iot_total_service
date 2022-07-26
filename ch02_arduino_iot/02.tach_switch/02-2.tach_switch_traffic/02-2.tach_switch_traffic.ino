int key=2;
int red=11;
int yellow=9;
int green=7;
int status=0;
char buf[18];

void setup() {
    Serial.begin(9600);
    pinMode(key, INPUT_PULLUP);
    pinMode(red, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);
    digitalWrite(red, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
}

void loop() {
    if(digitalRead(key) == LOW){
        sprintf(buf, "Key value : %d", digitalRead(key));
        Serial.println(buf);
        switch(status){
            case 0:
                digitalWrite(red, LOW);  digitalWrite(yellow, HIGH); digitalWrite(green, LOW);
                status=1;
                break;
            case 1:
                digitalWrite(red, LOW); digitalWrite(yellow, LOW); digitalWrite(green, HIGH);
                status=2;
                break;
            case 2:
                digitalWrite(red, LOW); digitalWrite(yellow, HIGH); digitalWrite(green, LOW);
                status=3;
                break;
            case 3:
                digitalWrite(red, HIGH); digitalWrite(yellow, LOW); digitalWrite(green, LOW);
                status=0;
                break;
        }
        sprintf(buf, "Status : %d", status);
        Serial.println(buf);
        delay(1000);
    }
}
