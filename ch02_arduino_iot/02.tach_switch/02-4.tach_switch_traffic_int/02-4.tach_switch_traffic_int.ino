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
    attachInterrupt(0, status_chg, FALLING);
}

void loop() {
    switch(status){
        case 0:
            digitalWrite(red, LOW);  
            digitalWrite(yellow, HIGH);
            digitalWrite(green, LOW); 
            delay(1000);
            status=1;
            break;
        case 1:
            digitalWrite(red, LOW); 
            digitalWrite(yellow, LOW); 
            digitalWrite(green, HIGH);
            break;
        case 2:
            digitalWrite(red, LOW); 
            digitalWrite(yellow, HIGH);
            digitalWrite(green, LOW);
            delay(1000);
            status=3; 
            break;
        case 3:
            digitalWrite(red, HIGH); 
            digitalWrite(yellow, LOW); 
            digitalWrite(green, LOW);
            break;
    }
}

void status_chg(){
    delay(100);
    if(digitalRead(key)==LOW){
        Serial.println("Key Interrupted ~~~~");
        if(status == 0)
            status=1;
        else if (status == 1)
            status=2;
        else if (status == 2)
         status=3;
        else if (status == 3)
            status = 0;
    }
}
