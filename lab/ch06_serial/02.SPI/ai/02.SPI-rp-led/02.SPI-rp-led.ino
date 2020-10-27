#include <SPI.h>

int led=8;

char buf [100];
volatile bool process_it;
volatile byte pos;
byte val, c;

void setup (void)
{
    Serial.begin (9600);   // debugging
    pinMode(led, OUTPUT);
    Serial.println(__FILE__);

    // turn on SPI in slave mode
    SPCR |= bit (SPE);
    
    // have to send on master in, *slave out*
    pinMode (MISO, OUTPUT);
    
    // get ready for an interrupt
    process_it = false;
    
    // now turn on interrupts
#if 1
    SPI.attachInterrupt();
#else
    SPCR |= bit(SPE);   // SPI 활성화
    SPCR &= ~bit(MSTR); // Slave 모드 선택
    SPCR |= bit(SPIE);  // 인터럽트 허용
#endif

}  // end of setup


// SPI interrupt routine
ISR (SPI_STC_vect){
    c = SPDR;  // grab byte from SPI Data Register
    process_it=true;

    if (pos < sizeof buf) {
        buf [pos++] = c;

    // example: newline means time to process buffer
        if (c == '\n')
        process_it = true;

    }  // end of room available
    
}  // end of interrupt routine SPI_STC_vect

// main loop - wait for flag set in interrupt routine
void loop () {
    Serial.write(val); Serial.write('\n');
    if (process_it) {
        buf [pos] = 0;
        int buff = atoi(buf);
        Serial.println (buff);
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
    delay(1000);
}  // end of loop
