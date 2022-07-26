#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <gattlib.h>

#define BLE_SCAN_TIMEOUT   3

#define	FILE_LED	"/var/www/html/rp_ws/ledstate"

static uuid_t g_uuid;

char *bdaddr = "F0:C7:7F:ED:E4:2D";		//educafe MAC address
char *uuid = "0000ffe1-0000-1000-8000-00805f9b34fb";
int gatt_connected;
long int value_data;
gatt_connection_t* connection;

static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

int led_onoff(long int value_data) {
	int ret;
	
	if (gattlib_string_to_uuid(uuid, strlen(uuid) + 1, &g_uuid) < 0) {
		fprintf(stderr, "Usage : \n");
		return 1;
	}
	
	connection = gattlib_connect(NULL, bdaddr, GATTLIB_CONNECTION_OPTIONS_LEGACY_DEFAULT);
	if (connection == NULL) {
		fprintf(stderr, "Fail to connect to the bluetooth device.\n");
		return 1;
	}
	
	ret = gattlib_write_char_by_uuid(connection, &g_uuid, &value_data, sizeof(value_data));
	
	if (ret != GATTLIB_SUCCESS) {
		char uuid_str[MAX_LEN_UUID_STR + 1];
		gattlib_uuid_to_string(&g_uuid, uuid_str, sizeof(uuid_str));

		if (ret == GATTLIB_NOT_FOUND) {
			fprintf(stderr, "Could not find GATT Characteristic with UUID %s. "
				"You might call the program with '--gatt-discovery'.\n", uuid_str);
		} else {
			fprintf(stderr, "Error while writing GATT Characteristic with UUID %s (ret:%d)\n",
				uuid_str, ret);
		}
		gattlib_disconnect(connection);
	}
	gattlib_disconnect(connection);
	return 0;
}

typedef void (*ble_discovered_device_t)(const char* addr, const char* name);

// We use a mutex to make the BLE connections synchronous
// static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

static void ble_discovered_device(void *adapter, const char* addr, const char* name, void *user_data) {
	struct connection_t *connection;
	int ret;
#if 0
	if (name) {
		printf("Discovered %s - '%s'\n", addr, name);
	} else {
		printf("Discovered %s\n", addr);
	}
#endif
}

int main(int argc, const char *argv[]) {
	const char* adapter_name;
	void* adapter;
	int ret, led_val;
	int fd;
	char buf[80];
	pid_t	pid;
	
	if((pid = fork()) != 0) exit(0);
	setsid();
	if(chdir("/") != 0) {
		perror("chdir");
		exit(1);
	}
	syslog(LOG_INFO|LOG_DAEMON, "Led Control daemon process start(%d)!!\n", getpid());

	puts("Scan started");
	ret = gattlib_adapter_open(adapter_name, &adapter);
	if (ret) {
		fprintf(stderr, "ERROR: Failed to open adapter.\n");
		return 1;
	}
	
	ret = gattlib_adapter_scan_enable(adapter, ble_discovered_device, BLE_SCAN_TIMEOUT, NULL /* user_data */);
	if (ret) {
		fprintf(stderr, "ERROR: Failed to scan.\n");
		gattlib_adapter_close(adapter);
		return ret;
	}

	gattlib_adapter_scan_disable(adapter);
	puts("Scan completed");
	
#if 1
	if(0==access(FILE_LED, F_OK)) unlink(FILE_LED);
	
	if( mkfifo(FILE_LED, 0666) < 0 ) {
		syslog(LOG_INFO|LOG_DAEMON, "Led Control fifo file create error!!(%d)!!\n", getpid());
		exit(1);
	}
	system("chmod 666 /var/www/html/rp_ws/ledstate");
		
	if( (fd = open(FILE_LED, O_RDWR)) < 0 ) {
		syslog(LOG_INFO|LOG_DAEMON, "Led Control file open error!!(%d)!!\n", getpid());
		exit(1);
	}
#endif
	
	while(1) {
		memset(buf, 0, sizeof(buf));
		read(fd, buf, sizeof(buf));
		syslog(LOG_INFO|LOG_DAEMON, "Led FIFO read(%s)!!\n", buf);

		if( strncmp(buf, "on", 2) == 0 ) 
			led_val = '1';
		else 
			led_val = '0';
		led_onoff(led_val);
		sleep(1);
	}
	
	// close(fd);
	
}


/*
gcc 03.ws_ad_led_onoff.c -o ws_led -lgattlib
*/
