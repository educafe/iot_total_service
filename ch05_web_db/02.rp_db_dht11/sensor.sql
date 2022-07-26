
mysql> source sensor.sql


CREATE DATABASE mydb1 CHARACTER SET utf8 COLLATE utf8_general_ci;

show databases;

use mydb1;
show tables;

create table dht11 (
	id int(11) NOT NULL AUTO_INCREMENT,
	temperature_humidity varchar(50) NOT NULL,
	created datetime NOT NULL,
	PRIMARY KEY (id)
) DEFAULT CHARSET=utf8;


insert into dht11(temperature_humidity, created) values('Humidity=23.21% Temperature=32.31*C[4.1*F]', '2015-2-05 10:02:05');

insert into dht11(temperature_humidity, created) values('Humidity=23.21% Temperature=32.31*C(4.1*F)', now());

select * from dht11;

select id,temperature_humidity from dht11 where id=3;

select * from dht11 order by id desc limit 5;


desc dht11;



