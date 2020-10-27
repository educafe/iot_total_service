1) bt_miniterm.c
============
--> $ sudo hcitool scan 명령을 통해 hc06 디바이스 mac 주소를 검색
--> $ sudo bluetoothctl  명령어 이후 agent on, scan 명령어를 통해서 확인 가능
--> $ 이후 pair <hc06 mac 주소> 명령어 실행으로 pairing 
---> 이 때 PIN 번호를 입력해야 함 ---> 대체로 1234, 또는 0000
--> 설정 이후 bt_miniterm.c 컴파일 (gcc bt_miniterm.c)
--> 실행 시 -b9600 -d/dev/rfcomm0 등 옵션을 추가해야 함. 이 때 프로토콜이 완성됨
--> 이후 키보드에서 1과 0을 교대로 입력

2) bt_rfcomm.c -- miniterm과 같은 통신 프로토콜을 직접 작성하는 것
=========================================
--> $ sudo hcitool scan 명령을 통해 hc06 디바이스 mac 주소를 검색
--> $ sudo bluetoothctl  명령어 이후 agent on, scan 명령어를 통해서 확인 가능
--> $ 이후 pair <hc06 mac 주소> 명령어 실행으로 pairing 
---> 이 때 PIN 번호를 입력해야 함 ---> 대체로 1234, 또는 0000
--> 설정 이후 bt_rfcomm.c 컴파일 (gcc rfcomm.com)
--> ./a.out 으로 실행하면 1과 0을 반복적으로 전송하여 LED가 on/off 된다

3) bt_rfcomm_client.c & bt_rfcomm_server.c
==============================
-->2대의 raspbery Pi를 이용하여 클라이언트-서버 관계로 구성하는 예제
--> /dev/rfcomm* 디바이스 파일을 사용하지 않고
--> bluetooth socket을 생성하여 소켓 통신(소켓 파일)을 하는 일반적인 네트워크 프로그래밍
---> socket - bind - listen - accept - recv/send (서버)
---> socket - connect 
--> bluetooth 프로토콜은 API 호출 시 라이브러리에서 완성해 준다
--> 컴파일 시 bluetooth 라이브러리와 링크를 해 주어야 함 ( -lbluetooth)
4) bt_rfcomm-hc06.c
==============
--> RaspberryPi와 Arduino 간 hc06을 통하여 LED를 제어하는 예제
--> RaspberryPi는 클라이언트로 Arduino에 연결된 hc06 디바이스가 server와 같은 역할을 함
--> 따라서 Bluetooth client 프로그램과 동일한 원리로 작성 후 컴파일
----> gcc bt_rfcomm-hc06.c -lbluetooth
----> ./a.out 1 (0을 argument로 주면 안됨)
--> RaspberryPi에서 Arduino로 1과 0을 반복으로 전송하여 Arduino에 연결된 LED를 on/off 한다