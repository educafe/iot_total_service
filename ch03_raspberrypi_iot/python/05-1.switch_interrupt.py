#coding: utf-8

import RPi.GPIO as GPIO
import time

#GPIO.setmode(GPIO.BOARD)
#LED=12
#KEY=18

GPIO.setmode(GPIO.BCM)
LED=18
KEY=26

GPIO.setup(LED, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(KEY, GPIO.IN, pull_up_down=GPIO.PUD_UP)

def handle(pin):
	global times
	global state
	for i in range(1, 100000):
		pass
	if(GPIO.input(pin) != state):
		times += 1
		if times == 11:
			times = 1
		print ('button clicked ' + repr(times))

try:
	GPIO.add_event_detect(KEY, GPIO.FALLING, handle, bouncetime=300)
	state = GPIO.input(KEY)
	times = 0
	
	while(True):
		GPIO.output(LED, GPIO.LOW)
		time.sleep(0.1*times)
		GPIO.output(LED, GPIO.HIGH)
		time.sleep(0.1*times)
		
except KeyboardInterrupt:
	pass

finally:
	print('Program End!')
	GPIO.cleanup()

	
