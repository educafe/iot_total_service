// LED ON-OFF
int led = 13;

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600); 
    pinMode(led, OUTPUT);
}

void loop() {
    digitalWrite(led, HIGH);        // turn the LED on (HIGH is the voltage level)
    delay(1000);                    // wait for a second
    digitalWrite(led, LOW);         // turn the LED off by making the voltage LOW
    delay(1000);                    // wait for a second
}
