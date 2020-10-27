#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

void devInit(int gno, int mode){
	if(mode==1) pinMode(gno, OUTPUT);
	else pinMode(gno, INPUT);
}

int main(int argc, char *argv[]){
	int led_gno, key_gno, key_in;
	
	if(argc < 3) {
		printf("Usage : %s LED_GPIO_NO KEY_GPIO_NO\n", argv[0]);
		exit(-1);
	}
	led_gno = atoi(argv[1]);
	key_gno = atoi(argv[2]);
	
	wiringPiSetup();
	devInit(led_gno, 1);
	devInit(key_gno, 0);
	while(1) {
		key_in = digitalRead(key_gno);
		if(key_in == 0) digitalWrite(led_gno, HIGH);
		else digitalWrite(led_gno, LOW);
	}
	return 0;
}

// $ gpio readall





