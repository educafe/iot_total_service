#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#define	DEVICE_FILENAME	"/dev/mem"
#define	BCM_IO_BASE	0x3F000000		
#define	GPIO_BASE	(BCM_IO_BASE + 0x200000)
#define	GPIO_SIZE	(256)
//( *(gpio+((g)/10)) 는 GPFSET1 레지스터를 지정
//GPFSET1의 Bit 24번을 0로 설정(input mode), 
//즉 GPIO18번을  output 모드로 설정하기 위해 000(~(111))을 24비트 이동, clear 하는 것과 동일
#define	GPIO_IN(g)		( *(gpio+((g)/10)) &= ~(7 << (((g)%10)*3)) )
//GPFSET1의 Bit 24번을 1로 설정, 즉 GPIO18번을  output 모드로 설정하기 위해 001을 24비트 이동
#define	GPIO_OUT(g)		( *(gpio+((g)/10)) |= (1 << (((g)%10)*3)) )
//( *(gpio+7)) 는 GPSET0 레지스터를 지정, 해당 레지스터의 18번째 비트를 1로 write
#define	GPIO_SET(g)		( *(gpio+7) = 1<<g )
//( *(gpio+7)) 는 GPSET0 레지스터를 지정, 해당 레지스터의 18번째 비트를 0로 write
#define	GPIO_CLR(g)		( *(gpio+10) = 1<<g )
#define	GPIO_GET(g)		( *(gpio+13) & (1<<g) )

#define	GPIO_LED	18

volatile unsigned int *gpio;

int main(void){
	int fd;
	void *gpio_map;
	int i;

	fd = open(DEVICE_FILENAME, O_RDWR|O_SYNC);
	if(fd < 0) {
		perror("/dev/mem file open error!!");
		exit(-1);
	} else printf("/dev/mem file open ok!!\n");

	gpio_map = mmap(NULL, GPIO_SIZE, PROT_READ|PROT_WRITE, 
				MAP_SHARED, fd, GPIO_BASE);
	if(gpio_map == MAP_FAILED) {
		printf("[APP]gpio_mmap error!!\n");
		exit(-2);
	}
	gpio = (volatile unsigned int *)gpio_map;
	printf("gpio mmap ok(addr:%p)!!\n", gpio);
	
	GPIO_OUT(GPIO_LED);
	for(i=0; i<5; i++) {
		GPIO_SET(GPIO_LED);
		sleep(1);
		GPIO_CLR(GPIO_LED);
		sleep(1);
	}	
	
	munmap(gpio_map, GPIO_SIZE);
	close(fd);
	printf("led end...\n");
	return 0;
}

