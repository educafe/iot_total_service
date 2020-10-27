#include <stdint.h>  
#include <unistd.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <getopt.h>  
#include <fcntl.h>  
#include <sys/ioctl.h>  
#include <linux/types.h>  
#include <linux/spi/spidev.h>
#include <wiringPi.h>  
#include <error.h>
  
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))  
#define LED	1
  
static const char *device = "/dev/spidev0.0";  
static uint8_t mode = 0;  
static uint8_t bits = 8;  
static uint32_t speed = 250000;  
static uint16_t delayed;  
  
uint8_t transfer(int fd, char* tx, int len)  
{  
    int ret;  
    uint8_t rx[256];  
    struct spi_ioc_transfer tr = {  
        .tx_buf = (unsigned long)tx,  
		.rx_buf = (unsigned long)rx,  
        .len = len,  
        .delay_usecs = delayed,  
        .speed_hz = speed,  
        .bits_per_word = bits,  
    };  
  
    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);  
    if (ret < 1) {
		perror("ioctl");
		exit(101);
	} 
 
    for (ret = 0; ret < len; ret++)   
        printf(" RESULT = %d - %d", rx[ret], ret);  
	
    puts("\n");
	return rx[0];
}  
  
  
int main(int argc, char *argv[])  
{  
    int ret = 0;  
    int fd;
	int i;
	uint8_t rst, rst1;
	
	wiringPiSetup();
	pinMode(LED, OUTPUT);
  
    fd = open(device, O_RDWR);  
    if (fd < 0)  {
		perror("can't open device");
		exit(102);
	}
       
    /* 
     * spi mode 
     */  
    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);  
    if (ret == -1)  {
		perror("can't set spi mode");
		exit(101);
	}

    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);  
    if (ret == -1) {
		perror("can't get spi mode");
		exit(101);
	}
  
    /* 
     * bits per word 
     */  
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);  
    if (ret == -1) {
		perror("can't set bits per word");  
		exit(101);
	} 
        
  
    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);  
    if (ret == -1){
		 perror("can't get bits per word");  
		 exit(101);
	} 
       
  
    /* 
     * max speed hz 
     */  
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);  
	
	if (ret == -1) {
		perror("can't set max speed hz");  
		exit(101);
	}
  
    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);  
    if (ret == -1) {
		perror("can't get bits per word");  
		exit(101);
	}
         
    printf("spi mode: %d\n", mode);  
    printf("bits per word: %d\n", bits);  
    printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);  
 
	for(;;){
		char buf[]="1"; 
		rst=transfer(fd, buf, sizeof(buf));
		sleep(1);
		char buf1[]="0";
		rst=transfer(fd, buf1, sizeof(buf));
		sleep(1);
	}

    close(fd);  
  
    return ret;  
}

