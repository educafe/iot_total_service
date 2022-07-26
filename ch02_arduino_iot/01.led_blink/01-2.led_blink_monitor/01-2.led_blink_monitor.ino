// LED ON-OFF
int led = 13;

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    pinMode(led, OUTPUT);
}

void loop() {
    if(Serial.available()){
        int val = Serial.read();
        if(val == 49){
            digitalWrite(led,HIGH);
        }
        else{
            digitalWrite(led, LOW);
        }
        Serial.println((val==49) ? "HIGH" : "LOW");
        delay(1000);
    }
}

