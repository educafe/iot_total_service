#include <stdio.h>  
#include <stdlib.h> 
#include <string.h>  
#include <unistd.h>  
#include <errno.h>   
#include <linux/i2c-dev.h>  
#include <sys/ioctl.h>  
#include <fcntl.h>    
    
#define ADDRESS 0x04  	//i2c address    
//I2C bus  
static const char *deviceName = "/dev/i2c-1";    
   
int main(int argc, char** argv)   
{  
    int fd, arg;
    unsigned char cmd;  
    char buf[1024]={0,};  
    if (argc < 2)   
    {  
        printf( "Usage:\n");  
        printf( "%s 1 : led control\n", argv[0] );  
        printf( "%s 2 : get temperature\n", argv[0] );  
        exit(1);  
    }        
    cmd = atoi(argv[1]);
   
    if ((fd = open( deviceName, O_RDWR ) ) < 0)   
    {  
        fprintf(stderr, "I2C: Failed to access %s\n", deviceName);  
        exit(1);  
    }  
    printf("I2C: Connected\n");   
   
    printf("I2C: acquiring bus to 0x%x\n", ADDRESS);  
    if (ioctl(fd, I2C_SLAVE, ADDRESS) < 0)   
    {  
        fprintf(stderr, "I2C: Failed to acquire bus access/talk to slave 0x%x\n", ADDRESS);  
        exit(1);  
    }    
   
    printf("Sending %d\n", cmd);
    if (write(fd, &cmd, 1) == 1)   {               
        usleep(10000);  
        read( fd, buf, 1024 );        
        puts( buf );  
    }  
 
    usleep(10000);  
    close(fd);  
    return 0;  
}  

