#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*
$ gpio mode 1 out
$ gpio write 1 1
$ gpio write 1 0
*/
int ledControl(int gpio){
	char cmd[64];
	printf("ledControl started....\n");

	sprintf(cmd, "gpio mode %d out", gpio);
	system(cmd);
	printf("gpio mode %d out... executed\n", gpio);
	getchar();
   
	for(;;){
#if 1
		sprintf(cmd, "gpio write %d 1", gpio);
		system(cmd);
		printf("gpio write %d 1 ... executed\n", gpio);
		sleep(1);
		sprintf(cmd, "gpio write %d 0", gpio);
		system(cmd);
		printf("gpio write %d 0... executed\n", gpio);
		sleep(1);
#else
		system("/usr/bin/gpio write 1 1");
		printf("gpio write 1 1 ... executed\n");
		sleep(1);
		system("/usr/bin/gpio write 1 0");
		printf("gpio write 1 0 ... executed\n");
		sleep(1);
#endif
	}
	return 0;
}

int main(int argc, char** argv){
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
