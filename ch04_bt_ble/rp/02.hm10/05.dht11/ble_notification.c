/*
 *
 *  GattLib - GATT Library
 *
 *  Copyright (C) 2016-2017  Olivier Martin <olivier@labapart.org>
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <assert.h>
#include <glib.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "gattlib.h"

#define BLE_SCAN_TIMEOUT   3

// hm10 chdracteristics uuid
const uuid_t g_hm10_char_uuid = CREATE_UUID16(0xffe1);

static GMainLoop *m_main_loop;

void notification_handler(const uuid_t* uuid, const uint8_t* data, size_t data_length, void* user_data) {
	int i;

	printf("Notification Handler: ");
	printf("%s\n", data);
}

static void on_user_abort(int arg) {
	g_main_loop_quit(m_main_loop);
}

static void usage(char *argv[]) {
	printf("%s <device_address>\n", argv[0]);
}

#if 1

typedef void (*ble_discovered_device_t)(const char* addr, const char* name);

static void ble_discovered_device(void *adapter, const char* addr, const char* name, void *user_data) {
	struct connection_t *connection;
	int ret;
#if 0				// BLE 디바이스를 스캔한 결과를 출력할지 여부를 결정
	if (name) {
		printf("Discovered %s - '%s'\n", addr, name);
	} else {
		printf("Discovered %s\n", addr);
	}
#endif
}

#endif

int main(int argc, char *argv[]) {

// adapter_name을 이용하여 adapter 객체를 생성하는데 adaptor 이름을 지정하면 에러가 발생한다.
// 그 원인은 build top의 /dbus/gattlib.c 파일에서 찾아야 한다.. 
#if 1		
	const char* adapter_name;
	void* adapter;
#endif	
	
	int ret;
	gatt_connection_t* connection;

	if (argc != 2) {
		usage(argv);
		return 1;
	}

// 라즈베리파이에서 이전에 디바이스를 한번도 scan 한 적이 없는 경우 에러가 발생하기 때문에
// 본 프로그램을 처음 실행하는 경우에는 BLE 디바이스 스캔을 먼저 실행해서 'educafe' 디바이스를 찾아야 한다
// 해당 디바이스의 MAC 주소를 argv[1]로 입력하여야 한다
// sudo hcitool lescan 명령을 통해서 먼저 확인할 수 있다 
#if 1 	
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

#endif
	
	connection = gattlib_connect(NULL, argv[1], GATTLIB_CONNECTION_OPTIONS_LEGACY_DEFAULT);
	if (connection == NULL) {
		fprintf(stderr, "Fail to connect to the bluetooth device.\n");
		return 1;
	}

	gattlib_register_notification(connection, notification_handler, NULL);

	ret = gattlib_notification_start(connection, &g_hm10_char_uuid);
	if (ret) {
		fprintf(stderr, "Fail to start notification.\n");
		goto DISCONNECT;
	}

	// Catch CTRL-C
	signal(SIGINT, on_user_abort);

	m_main_loop = g_main_loop_new(NULL, 0);
	g_main_loop_run(m_main_loop);

	// In case we quit the main loop, clean the connection
	gattlib_notification_stop(connection, &g_hm10_char_uuid);
	g_main_loop_unref(m_main_loop);

DISCONNECT:
	gattlib_disconnect(connection);
	puts("Done");
	return ret;
}


/*
To compile, 
gcc ble_notification.c -lgattlib $(pkg-config --cflags --libs glib-2.0)
./a.out F0:C7:7F:ED:E4:2D (educafe MAC address)

If necessary,(not mandatory, try one by one)
sudo apt-get install libglib2.0-dev
apt-get install libgtk2.0-dev
apt-get install glade 
*/