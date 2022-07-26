int led=13;
int key=2;
void setup() {
    Serial.begin(9600);
    Serial.print("Sketch : ");
    Serial.println(__FILE__);
    Serial.print("Uploaded : ");   
    Serial.println(__DATE__);
    Serial.println(" "); 

//    pinMode(key, INPUT);        //same as INPUT_PULLUP used with digitalWrite
    pinMode(key, INPUT_PULLUP);
    pinMode(led, OUTPUT);
}
boolean sw = false;


void loop() {
    while( digitalRead(key) == LOW ) {
        Serial.println(sw ? "HIGH" : "LOW");
        if(sw) {
            digitalWrite(led, LOW);
        } else {
            digitalWrite(led, HIGH);
        }
        sw = !sw;
        delay(1000);
  }
}
