#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*
$ echo "18" > /sys/class/gpio/export
$ echo "out" > /sys/class/gpio/gpio18/direction
$ echo "1" > /sys/class/gpio/gpio18/value
$ echo "0" > /sys/class/gpio/gpio18/value
$ echo "18" > /sys/class/gpio/unexport
*/

#define BUFSIZE	64
int ledControl(int gpio)
{
	int i;
	int fd;
	char buf[BUFSIZ];
	
	fd = open("/sys/class/gpio/export", O_WRONLY);          /* 해당 GPIO 장치 사용 준비 */
	if(fd == -1){
		perror("open1");
		exit(1);
	}
	
	sprintf(buf, "%d", gpio);
	if(write(fd, buf, strlen(buf)) == -1){
		perror("write1");
		close(fd);
		exit(1);
	}
   
   for(i=0; i<10000000; i++);

   sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);      /* 해당 GPIO 장치의 방향 설정 */
   fd = open(buf, O_WRONLY);
   if(fd == -1){
	   perror("open2");
	   exit(1);
   }
   /* 장치를 LED 출력을 위해서 설정 : 입력의 경우 write(fd, "in", 2); 사용 */
   if(write(fd, "out", 3)== -1){
		perror("write2");                                                          
		close(fd);
		exit(1);
   }

   sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);          /* 장치에 값 출력 */
   fd = open(buf, O_WRONLY);
   if(fd == -1){
	   perror("open3");
	   exit(1);
   }
   if(write(fd, "1", 1) == -1){
		perror("write3");
		close(fd);
		exit(1);
   }
   sleep(2);
   if(write(fd, "0", 1)== -1){
	   perror("write4");
	   close(fd);
	   exit(1);
   }
   close(fd);

   fd = open("/sys/class/gpio/unexport", O_WRONLY);     /* 사용한 GPIO 장치 해제하기 */
   if(fd == -1){
	   perror("open3");
	   exit(1);
   }
   sprintf(buf, "%d", gpio);
   write(fd, buf, strlen(buf));
   close(fd);

   return 0;
}

int main(int argc, char** argv)
{
   int gno;

   if(argc < 2) {
      printf("Usage : %s GPIO_NO\n", argv[0]);
      return -1;
   }
   gno = atoi(argv[1]);

   ledControl(gno);

   return 0;
}

//BCM(GPIO)-18
//$ sudo ./a.out 18
/*
$ gpio -g mode 18 out
$ gpio -g write 18 1
$ gpio -g write 18 0

$ gpio export 18 out
$ gpio -g write 18 1
$ gpio unexport 18

$ gpio readall  (GPIO18 -> Wpi 1)
$ gpio mode 1 out
$ gpio write 1 1
$ gpio write 1 0
*/
