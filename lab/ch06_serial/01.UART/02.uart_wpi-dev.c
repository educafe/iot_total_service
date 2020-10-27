#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>

void MyPutc(char ch);
void MyGets(char *str);
int fd;

int main(void)
{
	char buff[100] = {0,};
	int i;

	if( wiringPiSetup() == -1) {
		perror("wiringPiSetup() Error");
		exit(1);
	}

	// fd = serialOpen("/dev/ttyACM0", 9600);
	fd = serialOpen("/dev/ttyS0", 9600);
	if(fd < 0) {
		perror("serialOpen() Error");
		exit(2);
	}

	printf("Usart Led Test Initial Done!!\n");
	for (i=0; i<10; i++){
		MyPutc('1');
		MyGets(buff);
		printf("Rx Data : %s\n", buff);
		sleep(1);
		MyPutc('0');
		MyGets(buff);
		printf("Rx Data : %s\n", buff);
		sleep(1);
	}
	
		serialClose(fd);
	printf("Program End!!\n");
	return 0;
}

void MyPutc(char ch) {
	serialPutchar(fd, ch);
}

void MyGets(char *buff) {
	int data;
	while(1) {
		data = serialGetchar(fd);
		if(data == '\r' || data == '\n') break;
		*buff++ = data;
	}
	*buff = '\0';
}
	
