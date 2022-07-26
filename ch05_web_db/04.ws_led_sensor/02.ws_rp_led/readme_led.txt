본 예제는 RaspberryPi에 웹서버를 설치한 후 웹 페이지를 통해서 
RaspberryPi에 연결되어 있는 LED를 제어하고
RaspberryPi에 연결되어 있는 센서 데이터를 읽는 것

1) ws_rp_led.c 파일
-------------------
웹서버를 통해 웹페이지로 전달되어 온 LED 제어 정보를 이용하여 
RaspberryPi에 연결되어 있는 LED를 제어하는 데몬 프로그램.
ledctl.php로 부터 LED 제어정보를 받아들여 RaspberryPi에 연결된 LED를 on/off 한다 

2) index.php 파일
-------------------
웹 브라우저를 통해 접속해 오는 경우(raspberrypi.mshome.net/~~) 초기 화면을 제공하는 웹페이지로
제어목록 (LED, Sensor 제어)를 제시하는 UI 이며

3) 2.txt
---------
선택한 목록에 따라 서버로 전송할 데이터(on/off)를 form 형태로 작성하여 전송
데이터가 GET 방식으로 전송되어 오면 ledctl.php 프로그램이 제어한다

4)ledctl.php
---------------
LED를 제어하기 위한 웹서버 프로그램으로 1)에서 실행시킨 LED 제어 데몬 프로그램에게 
UI를 통해 사용자가 전송해 온 LED 제어 데이터를 파이프를 통해 전달하는 프로그램