#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 30

int main(int argc, char *argv[]){
	int fd;
	int led;
	int i;
	int ret;

	fd=open("/dev/rfcomm0", O_RDWR);
	if(fd==-1){
		perror("open!!");
		exit(1);
	}
	
		
for(i=0; i<10; i++){
	printf("Send to Arduino (1)\n");
	ret=write(fd, "1", 1);
	sleep(3);
	printf("Send to Arduino (0)\n");
	write(fd, "0", 1);
	sleep(3);
}
	
	close(fd);
	return 0;
}
