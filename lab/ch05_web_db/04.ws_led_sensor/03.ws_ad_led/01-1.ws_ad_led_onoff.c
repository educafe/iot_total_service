#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <fcntl.h>
#include <syslog.h>
#include <wiringPi.h>

#include <sys/stat.h>

#define	FILE_LED	"/var/www/html/rp_ws/ledstate"
#define	LED_PIN		(1)
#define HOME		"/home/pi/iot_network/lab/ch05_web_db/04.ws_led_sensor/03.ws_ai_led"

char *bdaddr = "F0:C7:7F:ED:E4:2D";
char *uuid = "0000ffe1-0000-1000-8000-00805f9b34fb";
	
int led_onoff(int led_val) {
	pid_t pid;
	pid=fork();
	if(pid==0){
		if(led_val == 0){
			execl("/home/pi/iot_network/lab/ch05_web_db/04.ws_led_sensor/03.ws_ai_led/read_write", \
			"read_write", "F0:C7:7F:ED:E4:2D", "write", "ffe1", "48", (char *)0);
			perror("execl failed");
		}else if (led_val == 1){
			execl("/home/pi/iot_network/lab/ch05_web_db/04.ws_led_sensor/03.ws_ai_led/read_write", \
			"read_write", "F0:C7:7F:ED:E4:2D", "write", "ffe1", "49", (char *)0);
			perror("execl failed");
		}
	} 
	return 0;
}

int main(int argc, char *argv[]) {
	pid_t pid;
	int fd;
	char buf[80];
	int led_val=0;

	if((pid = fork()) != 0) exit(0);
	setsid();
	if(chdir("/") != 0) {
		perror("chdir");
		exit(1);
	}
	syslog(LOG_INFO|LOG_DAEMON, "Led Control daemon process start(%d)!!\n", getpid());
	
#if 0
	if(0==access(FILE_LED, F_OK)) unlink(FILE_LED);
#endif
	
	// led_init();
#if 0
	if( mkfifo(FILE_LED, 0666) < 0 ) {
		syslog(LOG_INFO|LOG_DAEMON, "Led Control fifo file create error!!(%d)!!\n", getpid());
		exit(1);
	}
	system("chmod 666 /var/www/html/rp_ws/ledstate");
		
	if( (fd = open(FILE_LED, O_RDWR)) < 0 ) {
		syslog(LOG_INFO|LOG_DAEMON, "Led Control file open error!!(%d)!!\n", getpid());
		exit(1);
	}
#endif
	
#if 0
	write(fd, "off", 3);
	close(fd);
#endif
	
	int i;
	
	for(i=0; i<6; i++) {
		led_onoff(!led_val);
		sleep(5);
		led_val=!led_val;
	}
	
	close(fd);
	printf("Program End !!!\n");
	exit(0);
}

//$ gpio readall
// BCM-18 -> wpi-1
// gcc ws_led.c -o ws_led -lwiringPi





