int key=2;
int led=12;

void setup() {
    pinMode(key, INPUT_PULLUP);
    pinMode(led, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    if( digitalRead(key) == HIGH ) 
        digitalWrite(led, LOW);
    else {
        digitalWrite(led, HIGH);
        Serial.println("Switch On");
    }
}
