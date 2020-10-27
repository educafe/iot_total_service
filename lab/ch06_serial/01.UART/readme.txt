***
Raspberry Pi에서 Serial 통신을 하기 위해서는 해당 모듈을 enable (raspi-config) 하고,
console로 연결되어 있는 serial port 구성을 device 파일로 전환해야 한다 
--> cmdlint.txt 파일에서 console 부분을 삭제한 후 재부팅하면 /dev/serial0 -> ttyS0 파일이 생성된다

1) uart_serial.c
===========
-> 아두이노에는 HWserialrxtx.ino 파일이 로드되고, 
-> 수신된 문자열을 모니터 화면에 보여주고, 다시 수신된 문자열을 라즈베리파이로 반환
-> 라즈베리파이에서는 수신된 문자열을 보여준다

2) uart_wpi-dev.c
=============
-> 리눅스 디바이스 파일을 활용한 Serial 통신
-> Arduino에 LED on/off ino을 로드 (04.SwSerial-Led.ino)
--> 컴파일 (gcc -lwiringPi) 후 실행
-> LED가 on/off 되면서 수신한 문자열(on, off)을 출력한다
-->uart serial 통신이므로 arduino에서 '\r' 또는 '\n' 문자를 수신하여야 화면에 출력한다
--> Arduino에서 println을 사용하면 문자열(ASCII 포멧)과 '\r' 또는 '\n' 문자가 같이 수신되므로
--> Arduino에서 mySerial.write 를 사용하여 binary bit 형식으로 전송하도록 하여야 한다

3) uart_wpi-led.c
============
-> Arduino에 cds 센서를 구성하고 cds 센서 값을 읽어서 Serial 통신으로 Raspberry Pi로 전송
-> Raspberry Pi에서 수신된 cds 값을 확인 한 후 LED를 on/off 하는 예제