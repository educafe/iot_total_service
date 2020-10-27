#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <signal.h>
#include <syslog.h>

int gno;
void sig_handler(int signo){
	pwmWrite(gno, 0);
	syslog(LOG_INFO, "exit (%d)\n", 101);
	exit(101);
}

int led_onoff(int gno){
	int i,j;
	for(;;){
		for(i=0; i<1024; i++){
			pwmWrite(gno, i);
			delay(1);
		}
		delay(100);
		for (j = 1023; j >= 0; --j){
			pwmWrite(gno, j);
			delay(1);
		}
		delay (100) ;
	}
	return 0;
}

int main(int argc, char *argv[]){
	// int gno;
	
	openlog("02.led_pwm", LOG_PID|LOG_CONS, LOG_USER);
	
	if(argc < 2) {
		printf("Usage : %s GPIO_NO\n", argv[0]);
		exit(100);
	}
	
	printf ("Raspberry Pi wiringPi PWM test program\n") ;
	signal(SIGINT, sig_handler);
	
	gno = atoi(argv[1]);
	
	wiringPiSetup();
	
	pinMode(gno, PWM_OUTPUT);
	
	led_onoff(gno);
	
	return 0;
}

//$ gpio readall
// BCM-18 -> wpi-1






