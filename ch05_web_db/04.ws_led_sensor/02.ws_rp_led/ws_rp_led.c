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

int led_init() {
	wiringPiSetup();
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);
}
	
int led_onoff(int led_val) {
	//pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, led_val);
	syslog(LOG_INFO|LOG_DAEMON, "Led Write(%d)!!\n", led_val);
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

	if(0==access(FILE_LED, F_OK)) unlink(FILE_LED);
	
	led_init();

	if( mkfifo(FILE_LED, 0666) < 0 ) {
		syslog(LOG_INFO|LOG_DAEMON, "Led Control fifo file create error!!(%d)!!\n", getpid());
		exit(1);
	}
	system("chmod 666 /var/www/html/rp_ws/ledstate");
		
	if( (fd = open(FILE_LED, O_RDWR)) < 0 ) {
		syslog(LOG_INFO|LOG_DAEMON, "Led Control file open error!!(%d)!!\n", getpid());
		exit(1);
	}
#if 0
	write(fd, "off", 3);
	close(fd);
#endif
	
	while(1) {
		memset(buf, 0, sizeof(buf));
		read(fd, buf, sizeof(buf));
		syslog(LOG_INFO|LOG_DAEMON, "Led FIFO read(%s)!!\n", buf);

		if( strncmp(buf, "on", 2) == 0 ) led_val = 1;
		else led_val = 0;
		
		led_onoff(led_val);
	}
	
	close(fd);
	return 0;
}

//$ gpio readall
// BCM-18 -> wpi-1
// gcc ws_led.c -o ws_led -lwiringPi





