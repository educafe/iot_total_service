#include <wiringPi.h>
#include <stdio.h>

#define MAXTIMINGS 85
#define DHTPIN 1	//GPIO18
// #define DHTPIN 6	//GPIO25

int dht11_dat[5] = {0,};

void read_dht11_dat() {
    unsigned short laststate = HIGH;
    unsigned short counter = 0;
    unsigned short j = 0, i;
    float f;
	

    dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

    pinMode(DHTPIN, OUTPUT);
    digitalWrite(DHTPIN, LOW);
    delay(18);
    digitalWrite(DHTPIN, HIGH);

    delayMicroseconds(40);
    pinMode(DHTPIN, INPUT);

    for (i = 0; i < MAXTIMINGS; i++) {
        counter = 0;
        while(digitalRead(DHTPIN) == laststate) {	//dht핀의 값이 high로 지속되는 시간 check (us)
            counter++;
            delayMicroseconds(1);
            if (counter ==255) break;
        }

        laststate = digitalRead(DHTPIN);		// laststate toggle, 즉 정상적으로 while 문을 빠져나오는 경우는 상태가 바뀔때

        if (counter == 255)
            break;

        if ((i >= 4) && (i % 2 == 0)) {
            dht11_dat[j/8] <<= 1;
            if (counter > 25)       	// this check is how long the pulse width is low.
                dht11_dat[j/8] |= 1;
            j++;
        }
    }

    if ((j >= 40) && (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF ))) {
        f = dht11_dat[2] * 9. / 5. + 32;
        printf("Humidity = %d.%d %% Temperature = %d.%d C (%.1f F)\n",
               dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f);
    } else {
        printf("Data not good, skip \n");
    }
}

int main(int argc, char **argv)
{
	if(wiringPiSetup() == -1) return -1;
	int wiringPiSetupGpio () ;


	while(1) {
		read_dht11_dat();
		delay(2000);
	}

	return 0;
}