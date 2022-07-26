#include <wiringPi.h>
#include <stdio.h>

#define MAX_COUNT 85
// #define DHT_PIN 1	//GPIO18
#define DHT_PIN 6	//GPIO25

int dhtVal[5] = {0,};

void readData(){
	unsigned short state = HIGH;
	unsigned short counter = 0;
	unsigned short j=0, i;
	float farenheit;

	// for(i=0; i<5; i++) dhtVal[i]=0;
	dhtVal[0] = dhtVal[1] = dhtVal[2] = dhtVal[3] = dhtVal[4] = 0;

	pinMode(DHT_PIN, OUTPUT);
	digitalWrite(DHT_PIN, LOW);		//MCU sends out start signal and pull down voltage for 18ms
	delay(18);						//to let DHT11 detect it
	digitalWrite(DHT_PIN, HIGH);	//MCU pull up voltage for 40ms to wait for response 
	delayMicroseconds(40);
	pinMode(DHT_PIN, INPUT);

	for(i=0; i<MAX_COUNT; i++) {
	  counter = 0;
	  while(digitalRead(DHT_PIN) == state) {
		counter++;
		delayMicroseconds(1);
		if(counter == 255) break;
	  }
	  state = digitalRead(DHT_PIN);
	  
	  if(counter == 255) 
		  break;

	  if((i>=4) && (i%2 == 0)) {
		dhtVal[j/8] <<= 1;
		if(counter > 32) 		//"17", calibration might be necessary if too many errors occurs too many
			dhtVal[j/8] |= 1;	// counter should be greater than 25 for stretch version
		j++;
	  }
	}

	printf("j(%d) => ", j);
	if((j >=40) && (dhtVal[4] == ((dhtVal[0] + dhtVal[1] + dhtVal[2] + dhtVal[3]) & 0xFF))) {
		farenheit = dhtVal[2]*9./5.+32;
		printf("Humidity = %d.%d %% Temparature = %d.%d *C (%.1f *F)\n",
		dhtVal[0], dhtVal[1], dhtVal[2], dhtVal[3], farenheit);
	} else printf("Invalid Data!!\n");

}

int main(int argc, char **argv)
{
	if(wiringPiSetup() == -1) return -1;

	while(1) {
		readData();
		delay(5000);
	}

	return 0;
}

