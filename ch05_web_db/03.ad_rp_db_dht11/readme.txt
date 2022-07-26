1) raspberrypi 디렉토리
======================
아두이노에서 수집한 dht11 센서 데이터를 라즈베리파이에서 파이썬 프로그램을 이용하여 수집한 다음,
mysql 데이터베이스에 저장하는 프로그램을 테스트 하는 디렉토리임.

2)bluedevice.py
==================
bledevice.py 파일은 항상 ble-hm10-temp-hum.py 프로그램이 실행되는 위치에 같이 존재해야한다.
ble-hm10-temp-hum.py 프로그램에서 bledevice.py 프로그램 내의 함수들을 호출하여 사용하기 때문이다

3) dht11 데이터의 BLE 통신
========================
라즈베리파이는 BLE의 notify 속성을 통해서 아두이노의 hm10으로부터의 dht11 데이터를 수신한다.
라즈베리파이는 BLE의 write-req 속성을 이용해서 아두이노의 LED를 제어한다

4)ble-notification-db.c
=============================
gattlib example 코드로 cmake를 통하지 않고 로컬에서 컴파일하는 방법은
----------------------------------------------------------------------------------
$ gcc ble_notification_db.c -lgattlib -lmysqlclient 명령을 실행 시
--> Glib.h : no such file or folder 에러메시지가 나온다. 이 때는 

sudo apt-get install libglib2.0-dev (이미 설치되어 있다고 출력됨)
sudo apt-get install libgtk2.0-dev (설치하지 않아도 되는지 확인 후 설치)
sudo apt-get install glade (실제는 설치하지 않았음)

gcc $(pkg-config --cflags --libs glib-2.0) notification.c -lgattlib -lmysqlclient 와 같이 실행

gattlib에 대한 내용은 해당 05.install_gattlib.sh 파일로 설치되는 내용을 참조