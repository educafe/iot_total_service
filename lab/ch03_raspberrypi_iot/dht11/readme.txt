1) dht11.py 파일을 삭제하면 안된다.
-> 02.temp_humid.py 파일에서 import를 하고 있기 때문이다

2) 01-1.temp_humid_jassie.c 파일은 RaspberryPi 3B 버전에서 실행
-> 3B+ 버전에서 실행하는 경우 counter>16 -> counter>25이상의 값으로 수정해야 한다
---> 클럭등의 차이가 있어서 발생