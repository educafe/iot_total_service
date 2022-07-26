#include <assert.h>
#include <glib.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "gattlib.h"


#include <mysql/mysql.h>

#define	DB_HOST		"127.0.0.1"
#define	DB_USER		"root"
#define	DB_PASS		"root"
#define	DB_NAME		"mydb1"
#define	DB_PORT		3306

// Battery Level UUID
// const uuid_t g_battery_level_uuid = CREATE_UUID16(0x2A19);
const uuid_t g_hm10__uuid = CREATE_UUID16(0xffe1);
char *bdaddr = "F0:C7:7F:ED:E4:2D";	

static GMainLoop *m_main_loop;
int interrupted = 0;
gatt_connection_t* connection;

int update_db(const unsigned char *temp) {
	MYSQL *connection=NULL, conn;
	MYSQL_RES *sql_rst;
	MYSQL_ROW sql_row;
	int query_stat;
	char query[1024];

	mysql_init(&conn);

	connection = mysql_real_connect(
		&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, (char*)NULL, 0);
	if(connection == NULL) {
		return 1;
	}

	sprintf(query, "insert into dht11(temperature_humidity, created) values('%s',now())", temp);
	query_stat = mysql_query(connection, query);
	if(query_stat != 0) {
		mysql_close(connection);
		return 1;
	}
	mysql_close(connection);
	return 0;
}


void notification_handler(const uuid_t* uuid, const uint8_t* data, size_t data_length, void* user_data) {
	int i;

	printf("Notification Handler: ");
	printf("%s\n", data);
	
	update_db(data);
	g_main_loop_quit(m_main_loop);
}

static void on_user_abort(int arg) {
	// g_main_loop_quit(m_main_loop);
	interrupted = 1;
}

static void usage(char *argv[]) {
	printf("%s <device_address>\n", argv[0]);
}

int main(int argc, char *argv[]) {
	int ret;
	// gatt_connection_t* connection;
	signal(SIGINT, on_user_abort);

REPEAT:	
	connection = gattlib_connect(NULL, bdaddr, GATTLIB_CONNECTION_OPTIONS_LEGACY_DEFAULT);
	if (connection == NULL) {
		fprintf(stderr, "Fail to connect to the bluetooth device.\n");
		return 1;
	}

	gattlib_register_notification(connection, notification_handler, NULL);
	ret = gattlib_notification_start(connection, &g_hm10__uuid);
	if (ret) {
		fprintf(stderr, "Fail to start notification.\n");
		goto DISCONNECT;
	}

	// Catch CTRL-C
	// signal(SIGINT, on_user_abort);

	m_main_loop = g_main_loop_new(NULL, 0);
	g_main_loop_run(m_main_loop);
	
	// In case we quit the main loop, clean the connection
	gattlib_notification_stop(connection, &g_hm10__uuid);
	g_main_loop_unref(m_main_loop);

DISCONNECT:
	gattlib_disconnect(connection);
	if (interrupted != 1){
		sleep(30);
		goto REPEAT;
	}
	puts("Done");
	return ret;
}


/*
Before it starts running and update db, table in db must be created first. 
Otherwise, creating table should be included in this program

To compile, 
gcc ble_notification_db.c -lgattlib $(pkg-config --cflags --libs glib-2.0) -lmysqlclient
./a.out F0:C7:7F:ED:E4:2D (educafe MAC address)

If necessary,(not mandatory, try one by one)
sudo apt-get install libglib2.0-dev
sudo apt-get install libgtk2.0-dev
sudo apt-get install glade 
*/