int pinButton = 2;
int LED = 13;
int stateLED = LOW;
int buttonState;
long startTime = 0;
long debounce = 200;

void setup() {
  pinMode(pinButton, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(pinButton);  
  if(buttonState == LOW && (millis() - startTime) > debounce) {
//  if(buttonState == HIGH && (millis() - startTime) > debounce) {
    Serial.println("Button pushed");
    if(stateLED == HIGH){
        stateLED = LOW; 
    } else {
       stateLED = HIGH; 
    }
    startTime = millis();
  }
  digitalWrite(LED, stateLED);
}
