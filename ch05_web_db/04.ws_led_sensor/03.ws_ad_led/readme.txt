read_write.c 파일은 github에서 제공해주는 원본 파일로 gattlib에서 제공하는 api를 이용하여
BLE 통신을 통해서 아두이노에 연결된 led를 on/off 할 수 있는 예제코드이다.

01.ws_ad_led_onoff 파일은 웹에서 라즈베리파이의 웹 서버를 통해 아두이노에 연결되어 있는 led를
on/off 할 수 있는 코드로 read_write.c 가 컴파일된 된 실행파일, read_write 을 그대로 사용 ble를 검증하는 프로그램이다. 따라서 컴파일시 gattlib가 필요없다.


02.ws_ad_led_onoff 파일은 웹에서 라즈베리파이의 웹 서버를 통해 아두이노에 연결되어 있는 led를
on/off 할 수 있는 응용 코드로 read_write.c에서 사용하는 gattlib 라이브러리의 api를 사용하므로
gattlib를 생성하여야 한다. gattlib가 생성된 후에는 컴파일시 gattlib 라이브러리를 링크해야 한다
-----------------------------------------------------------------------------------------------------------
$ gcc ws_led_onoff.c -o ws_led_onoff -lgattlib

cmake를 이용하여 gattlib 라이브러리를 만들기
-----------------------------------------------------

1) gattlib 생성을 위해 cmake를 실행할 때 필요한 라이브러리 설치
---------------------------------------------------------------------------
	$ sudo apt-get install libbluetooth-dev libreadline-dev 

2) cmake 설치
--------------------
	$ sudo apt install cmake

3) gattlib 빌드
------------------
	$ git clone https://github.com/labapart/gattlib.git
	$ cd gattlib (git clone을 실행한 top이다)
	$ mkdir build && cd build
	$ cmake ..
	$ make && sudo make install
	$ sudo ldconfig

cmame 실행시 아래와 같이 Document build시 에러가 발생하면
-----------------------------------------------------------------------
cmake  -DGATTLIB_BUILD_DOCS=OFF 으로 실행

cmake를 실행하고 나면 gattlib/examples 하위의 소스코드가 컴파일 된 후 실행파일이 
gattlib/build/example 하위의 각 예제마다 만들어진다.

gattlib/examples/read_write/read_write.c 소스코드를 수정한 후 컴파일하기
------------------------------------------------------------------------------------
	$ cd gattlib/example/read_write
	$ mkdir build
	$ cd build
	$ cmake ..
	$ make	를 실행하면 해당 폴더에 실행파일(read_write)이 생성된다


