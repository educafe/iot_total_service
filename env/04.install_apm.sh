#!/bin/bash
#install apache2 for web server
echo
echo -e $RED apt-get update$RESET
echo
sudo apt update
echo
echo
echo -e $RED"1) Install apache2"$RESET
echo
sudo  apt-get install -y apache2 
#install php7.0
echo
echo -e $RED"2) Install php7.0"$RESET
echo
sudo  apt-get install -y php
sudo  apt-get  install  libapache2-mod-php  -y
sudo  apt-get install php-mysql -y

echo
echo -e $RED"3) Install default-mysqlclient-dev"$RESET
echo
sudo  apt-get install -y default-libmysqlclient-dev
echo
echo -e $RED"4) Install mysql-connector-python-rf for apache2 and Django "$RESET
echo
sudo  pip install mysql-connector-python-rf
echo
echo -e $RED"6) Install pymysql"$RESET
echo
sudo pip install PyMySQL
echo
echo -e $RED"7) Install mariadb-server  mariadb-client "$RESET
echo

sudo  apt-get  install -y mariadb-server
sudo  apt-get  install -y mariadb-client
# sudo apt-get install mysql-server php-mysql -y
# Stretch 버전에서는 설치하는 과정
# sudo apt-get install mysql-server php-mysql -y
# 설치과정에서 root 비밀번호를 물어보지 않는 경우 설치 후에 다음과 같이 실행함

echo 
echo -e $RED"8) set root password"$RESET
sudo mysql_secure_installation

echo
echo -e $RED"9) To allow user to login without privileges"$RESET
echo -e $RED"Pleae do followings manually"$RESET
echo
# sudo mysql -u root
# use mysql
# update user set plugin='' where User='root';
# flush privileges;
# \q


#이후 MariaDB[none] 프롬프트 상에서 show databases; 를 입력하면
#생성되어 있는 database 목록을 보여주며, mydb1을 생성한 후 use mydb1을 입력하면
# MariaDB[mydb1] 등으로 프롬프트가 바뀌면서 이전과 동일한 작업을 할 수 있다
# RaspberryPi에서 vnc을 활성화 한 후 컴퓨터에서 vncviewer를 설치하여 원격접속