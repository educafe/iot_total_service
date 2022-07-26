#include <DHT11.h>    //DHT11_library.zip

int pin=8;            //Signal 이 연결된 아두이노의 핀번호
DHT11 dht11(pin); 
       
void setup() {
   Serial.begin(9600); //통신속도 설정
   pinMode(pin, INPUT_PULLUP);
}
 
void loop() {
    int err;
    float temp, humi;

    if((err=dht11.read(humi, temp))==0) {             //온도, 습도 읽어와서 표시
        Serial.print(" humidity:");
        Serial.print(humi);
        Serial.print("\t");
        Serial.print("temperature:");
        Serial.print(temp);
        Serial.println();
    } else {                                //에러일 경우 처리
        Serial.println();
        Serial.print("Error No :");
        Serial.print(err);
        Serial.println();    
    }
    delay(1000);                        //1초마다 측정
}
 
