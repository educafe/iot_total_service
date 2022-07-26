#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>


int main(int argc, char **argv){
    struct sockaddr_rc addr = { 0 };
    int btsfd;
		ssize_t ret;
		char dest[18] = "98:D3:61:F9:5B:6A";		//hc-06 chip MAC address (educafe)
    uint8_t ch;
		int i;
		char buf[128];

    if (argc != 2) {
      printf("Usage:\n");
      printf("\nrfcomm-client Channel\n");
      exit(1);
    }

    ch = (uint8_t)strtol(argv[1], NULL, 10);

    // allocate a socket
    btsfd = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
		if(btsfd == -1){
			perror("socket()");
			exit(1);
		}

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) ch;
    str2ba(dest, &addr.rc_bdaddr);

    // connect to server
    ret = connect(btsfd, (struct sockaddr *)&addr, sizeof(addr));
		if(ret == -1){
			perror("connect()");
			exit(1);
		}
	
    // send a signal to arduino
		for(i=0; i<3; i++){
			memset(&buf, 0, sizeof(buf));
			ret = write(btsfd, "ON\n", 3);
			sleep(1);
			ret = read(btsfd, &buf, sizeof(buf));
			printf("Returned from Arduino: %s\n", buf);
			usleep(1000000);
		
			memset(&buf, 0, sizeof(buf));
			write(btsfd, "OFF\n", 4);
			sleep(1);
			ret = read(btsfd, &buf, sizeof(buf));
			printf("Returned from Arduino: %s\n", buf);
			usleep(1000000);
		}
    close(btsfd);
    return 0;
}

//sudo apt-get install libbluetooth-dev to include <bluetooth/bluetooth.h> && rfcomm.h>
//gcc bt_rfcomm-hc06.c -o rfcomm -lbluetooth when compiling
// ./rfcomm 1 to execute the program
// only 1 rfcomm channel in hc-06 may be available.