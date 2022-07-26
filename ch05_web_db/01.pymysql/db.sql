show databases;

CREATE DATABASE mydb1 CHARACTER SET utf8 COLLATE utf8_general_ci;

show databases;

use mydb1;

create table dht11 (
	id int(11) NOT NULL AUTO_INCREMENT,
	temperature_humidity varchar(50) NOT NULL,
	created datetime NOT NULL,
	PRIMARY KEY (id)
) DEFAULT CHARSET=utf8;

show tables;

insert into dht11(temperature_humidity, created) values('Humidity=23.21% Temperature=32.31*C(4.1*F)', now());

SELECT * FROM dht11;




