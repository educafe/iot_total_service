#include <Wire.h>     
#define SLAVE_ADDRESS 0x09      //I2C 주소 지정 
int number = 0;  
int state = 0;  
int temp;  
char retMSG[1024] = "";   
const int led = 13;  
const int cds = A0; 
    
void setup() {  
    pinMode( led, OUTPUT);     
    Wire.begin(SLAVE_ADDRESS);  //슬레이브로써 I2C를 초기화한다.     
    //I2C 통신을 위한 콜백함수를 지정한다.  
    Wire.onReceive(receiveData); //데이터 수신용  
    Wire.onRequest(sendData);    //데이터 전송  
    Serial.begin(9600);
}    
   
void loop() {  
    delay(100);  
    temp = analogRead(cds);  
}     
  
void receiveData(int byteCount){     
    while(Wire.available()) {  
        number = Wire.read(); 
        Serial.println(number);     
        if (number == 1){
            Serial.println(number);  
            if (state == 0){  
                digitalWrite( led, HIGH ); // set the LED on  
                state = 1;  
                strcpy( retMSG, "Trun on LED\n");  
            }else{ 
                digitalWrite(13, LOW); // set the LED off  
                state = 0;  
                strcpy(retMSG, "Turn off LED\n");  
            }  
        }else if(number==2){  
            sprintf( retMSG, "Light = %d\n", temp );  
        }else{  
            sprintf( retMSG, "Invaild command\n" );  
        }  
    }  
}   
void sendData(){  
    Wire.write( retMSG, strlen(retMSG)+1 );  
}  

