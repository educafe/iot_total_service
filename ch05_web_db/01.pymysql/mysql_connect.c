#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include <mysql/mysql.h>

#define	DB_HOST		"127.0.0.1"
#define	DB_USER		"root"
#define	DB_PASS		"root"
#define	DB_NAME		"mydb1"
#define	DB_PORT		3306

int main(int argc, char *argv[]) {
	MYSQL *connection=NULL, conn;
	int query_stat;
	char query[1024];

	mysql_init(&conn);

	connection = mysql_real_connect(
		&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, (char*)NULL, 0);
	if(connection == NULL) {
		return 1;
	}

	sprintf(query, "insert into dht11(temperature_humidity, created) \
									values('Temp:33C, Humi:48%', now())");
	query_stat = mysql_query(connection, query);
	if(query_stat != 0) {
		mysql_close(connection);
		return 1;
	}
	mysql_close(connection);
	return 0;
}


/*
	Before it starts running and update db, table in db must be created first. 
	Otherwise, creating table should be included in this program

	To compile, 
	gcc mysql_connect.c -lmysqlclient
	./a.out 
*/