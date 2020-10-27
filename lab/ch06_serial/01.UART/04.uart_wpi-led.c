#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#define LED 1

void MyPutc(char ch);
void MyGets(char *str);
int fd;

int main(void)
{
	char buff[100] = {0,};
	int cds;
	

	if( wiringPiSetup() == -1) {
		perror("wiringPiSetup() Error");
		exit(1);
	}
	
	pinMode(LED, OUTPUT);

	// fd = serialOpen("/dev/ttyACM0", 9600);
	fd = serialOpen("/dev/ttyS0", 9600);
	if(fd < 0) {
		perror("serialOpen() Error");
		exit(2);
	}

#if 1
	for(;;){
		MyGets(buff);
		if(buff[0] == '\0' || buff[0] == '\r' || buff[0] == '\n')
			continue;
		cds=atoi(buff);
		printf("Rx Data : %d\n", cds);
		
		if(cds < 30){
			digitalWrite(LED, HIGH);
		}else{
			digitalWrite(LED, LOW);
;		}
	}
#else
	for(;;){
		read(fd, &cds, sizeof(cds));
		printf("Rx Data : %d\n", num);
		
		if(cds < 30){
			digitalWrite(LED, HIGH);
		}else{
			digitalWrite(LED, LOW);
		}
	}
	
#endif
	
	

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
	
