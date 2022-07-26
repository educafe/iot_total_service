#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

int led_onoff(int gno){
	int i;
	pinMode(gno, OUTPUT);
	
	for(i=0; i<5; i++) {
		digitalWrite(gno, HIGH);
		delay(1000);
		digitalWrite(gno, LOW);
		delay(1000);
	}
	return 0;
}

int main(int argc, char *argv[]){
	int gno;
	
	if(argc < 2) {
		printf("Usage : %s GPIO_NO\n", argv[0]);
		exit(-1);
	}
	gno = atoi(argv[1]);
	
	// wiringPiSetup();
	wiringPiSetupGpio();
	
	led_onoff(gno);
	
	return 0;
}

//$ gpio readall
// BCM-18 -> wpi-1






