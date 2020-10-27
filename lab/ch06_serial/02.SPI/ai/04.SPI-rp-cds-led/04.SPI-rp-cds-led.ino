#include <SPI.h>  

int cds = A5; 
int led=8;
int light;
char light_val[10];
byte val, c;

char buf [100];  
volatile byte pos = 0;  
volatile boolean printIt = false;  
volatile bool process_it;
#define   spi_enable()   (SPCR |= _BV(SPE))    
  
void setup (void)  
{  
    //시리얼 통신 초기화  
    Serial.begin (9600);  
    Serial.println(__FILE__);
   
    //Master Input Slave Output 12번핀을 출력으로 설정  
    pinMode(MISO, OUTPUT);  
    process_it = false;
    
    //slave 모드로 SPI 시작   
    spi_enable();  
   
    //인터럽트 시작  
    SPI.setClockDivider(SPI_CLOCK_DIV64); //250kHz   
    SPI.setDataMode(SPI_MODE0);  
    SPI.attachInterrupt();  
   
}      
   
// SPI 인터럽트 루틴  
ISR (SPI_STC_vect)  
{  
    // SPI 데이터 레지스터로부터 한바이트 가져옴  
     c = SPDR;  // grab byte from SPI Data Register
    process_it=true;

    if (pos < sizeof buf) {
        buf [pos++] = c;

    // example: newline means time to process buffer
        if (c == '\n')
        process_it = true;

    }  // end of room available
}    
   
  
void loop (void)  
{  

   if (process_it) {
        buf [pos] = 0;
        int buff = atoi(buf);
        Serial.print(buff);
        switch(buff) {
            case 1:
                digitalWrite(led, HIGH);
                break;
            case 0:
                digitalWrite(led, LOW);
                break;
        }
        pos = 0;
        process_it = false;
    }  // end of flag set

	int light = analogRead(cds);
    int val= map(light, 0, 1023, 0, 255);
	Serial.println(val, DEC);
     SPDR=val;
	delay(1000);	
      
}  
