#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <fcntl.h>
#include <syslog.h>
#include <wiringPi.h>

#include <sys/stat.h>

char *bdaddr = "F0:C7:7F:ED:E4:2D";		//educafe MAC address
char *uuid = "0000ffe1-0000-1000-8000-00805f9b34fb";
	
int main(int argc, char *argv[]) {
	int led_val;
	int rst;
	char tmp[128];

	while(1) {
		led_val='1';
		sprintf(tmp, "/home/pi/iot_network/lab/ch05_web_db/04.ws_led_sensor/03.ws_ai_led/read_write \
		%s write %s %d", bdaddr, uuid, led_val);
		system(tmp);
		sleep(1);
		led_val='0';
		sprintf(tmp, "/home/pi/iot_network/lab/ch05_web_db/04.ws_led_sensor/03.ws_ai_led/read_write \
		%s write %s %d", bdaddr, uuid, led_val);
		system(tmp);
		sleep(1);
	}
	
	return 0;
}

//$ gpio readall
// BCM-18 -> wpi-1
// gcc ws_led.c -lgattlib
// ./a.out을 실행하기 이전에 ble_scan 프로그램을 한 번 실행시킨 후 gattlib에 연결해야 한다.
// ble_scan 은 cmake를 통해 gattlib를 build 하고 나면 gattlib/build/examples 하위에 생성된다
// read_write.c 를 컴파일하여 동일한 디렉토리에 위치한 후 해당 프로그램이 호출이 가능하도록 PATH에 등록
// gcc read_write.c -i read_write -lgattlib
// PATH=$(pwd):PATH





