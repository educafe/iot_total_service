#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <fcntl.h>
#include <syslog.h>
#include <wiringPi.h>
#include <mysql/mysql.h>

#define	DB_HOST		"127.0.0.1"
#define	DB_USER		"root"
#define	DB_PASS		"root"
#define	DB_NAME		"mydb1"
#define	DB_PORT		3306

int sensor_read(char *buff);
#define MAX_COUNT 85
// #define DHT_PIN 1	//GPIO18
#define DHT_PIN 10	//GPIO25

int dhtVal[5] = {0,};
char temp[50]={0,};
char pre_temp[50]={0,};

void sensor_init() {
	int rst, i;
	sleep(10);
	wiringPiSetup();
	for(i=1; i<=5; i++) {
		rst = sensor_read(temp);
		if(rst==0) {
			strcpy(pre_temp, temp);
			break;
		} else {
			sleep(1);
		}
	}
	if(rst!=0) strcpy(pre_temp, "Humidity=00.00% Temperature=00.00*C[0.0*F]");

}

int sensor_read(char *buff) {
	unsigned short state = HIGH;
	unsigned short counter = 0;
	unsigned short j=0, i;
	float farenheit;

	for(i=0; i<5; i++) dhtVal[i]=0;

	pinMode(DHT_PIN, OUTPUT);
	digitalWrite(DHT_PIN, LOW);
	delay(18);
	digitalWrite(DHT_PIN, HIGH);
	delayMicroseconds(40);
	pinMode(DHT_PIN, INPUT);

	for(i=0; i<MAX_COUNT; i++) {
	  counter = 0;
	  while(digitalRead(DHT_PIN) == state) {
		counter++;
		delayMicroseconds(1);
		if(counter == 255) break;
	  }
	  state = digitalRead(DHT_PIN);
	  if(counter == 255) break;

	  if((i>=4) && (i%2 == 0)) {
		dhtVal[j/8] <<= 1;
		if(counter > 25) dhtVal[j/8] |= 1;
		j++;
	  }
	}

	if( (j >=40) && (dhtVal[4] == ( (dhtVal[0] + dhtVal[1] + dhtVal[2] + dhtVal[3]) & 0xFF) ) ) {
		farenheit = dhtVal[2]*9./55.+32;
		sprintf(buff, "Humidity=%d.%d%% Temparature=%d.%d*C(%.1f*F)", \
		dhtVal[0], dhtVal[1], dhtVal[2], dhtVal[3], farenheit);
		printf("BUFF: %s\n", buff);
		syslog(LOG_INFO|LOG_DAEMON, "Sensor Read => %s\n", buff);
		return 0;		//ok
	} else {
		sprintf(buff, "Invalid Data!!");
		printf("BUFF_INVALID: %s\n", buff);
		syslog(LOG_INFO|LOG_DAEMON, "Sensor Read => %s\n", buff);
		return 1;		//nok
	}
}

int create_table() {
	MYSQL *connection=NULL, conn;
	int query_stat;
	char query[1024];

	mysql_init(&conn);

	connection = mysql_real_connect(
		&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, (char*)NULL, 0);
	if(connection == NULL) {
		syslog(LOG_INFO|LOG_DAEMON, "MySQL connection error:%s", mysql_error(&conn));
		return 1;
	}

	sprintf(query, "create table dht11 (id int(11) NOT NULL AUTO_INCREMENT, temperature_humidity varchar(50) NOT NULL, created datetime NOT NULL, PRIMARY KEY (id)) DEFAULT CHARSET=utf8; ");
	query_stat = mysql_query(connection, query);
	if(query_stat != 0) {
		syslog(LOG_INFO|LOG_DAEMON, "MySQL table create query error:%s", mysql_error(&conn));
		mysql_close(connection);
		return 1;
	}
	mysql_close(connection);
	return 0;
}

int insert_table(char *temp) {
	MYSQL *connection=NULL, conn;
	MYSQL_RES *sql_rst;
	MYSQL_ROW sql_row;
	int query_stat;
	char query[1024];

	mysql_init(&conn);

	connection = mysql_real_connect(
		&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, (char*)NULL, 0);
	if(connection == NULL) {
		syslog(LOG_INFO|LOG_DAEMON, "MySQL connection error:%s", mysql_error(&conn));
		return 1;
	}

	sprintf(query, "insert into dht11(temperature_humidity, created) values('%s',now())", temp);
	query_stat = mysql_query(connection, query);
	if(query_stat != 0) {
		syslog(LOG_INFO|LOG_DAEMON, "MySQL insert query error:%s", mysql_error(&conn));
		mysql_close(connection);
		return 1;
	}
	mysql_close(connection);
	return 0;
}

#if 0
int show_table() {
	MYSQL *connection=NULL, conn;
	MYSQL_RES *sql_rst;
	MYSQL_ROW sql_row;
	int query_stat;
	char query[1024];

	mysql_init(&conn);

	connection = mysql_real_connect(
		&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, (char*)NULL, 0);
	if(connection == NULL) {
		fprintf(stderr, "MySQL connection error:%s", mysql_error(&conn));
		return 1;
	}

	sprintf(query, "select * from sensor");
	query_stat = mysql_query(connection, query);
	if(query_stat != 0) {
		syslog(LOG_INFO|LOG_DAEMON, "MySQL select query error:%s", mysql_error(&conn));
		return 1;
	}

	sql_rst = mysql_store_result(connection);
	printf("%-10s %-10s %-20s\n", "Id", "Temp", "Created");
	while( (sql_row = mysql_fetch_row(sql_rst)) != NULL )
	{
		printf("%-10s %-10s %-20s\n", sql_row[0], sql_row[1], sql_row[2]);
	}

	mysql_free_result(sql_rst);
	return 0;
}
#endif

int main(int argc, char *argv[]) {
	pid_t pid;
	int rst;

	if((pid = fork()) != 0) exit(0);
	setsid();
	if(chdir("/") != 0) {
		perror("chdir");
		exit(1);
	}
	syslog(LOG_INFO|LOG_DAEMON, "Sensor Control daemon process start(%d)!!\n", getpid());

	sensor_init();

	rst = create_table();
	if(rst==0) {
		syslog(LOG_INFO|LOG_DAEMON, "Sensor Table Created!!(%d)!!\n", getpid());
	} else {
		syslog(LOG_INFO|LOG_DAEMON, "Sensor Table Exist!!(%d)!!\n", getpid());
	}
	
	while(1) {
		rst = sensor_read(temp);
		if(rst != 0) strcpy(temp, pre_temp);
		else strcpy(pre_temp, temp);
		printf("PRE_TEMP: %s\n", pre_temp);
		printf("TEMP: %s\n", temp);
		rst = insert_table(temp);
		if(rst==0) {
			syslog(LOG_INFO|LOG_DAEMON, "Temp Sensor Write to DB OK!!(%s)!!\n", temp);
		} else {
			syslog(LOG_INFO|LOG_DAEMON, "Temp Sensor Write to DB ERROR!!(%s)!!\n", temp);
		}
		//sleep(300);
		sleep(30);
	}
	return 0;
}

//$ gpio readall
// BCM-18 -> wpi-1
// gcc rp_db_sensor.c -lwiringPi -lmysqlclient

		
