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

try:
	GPIO.add_event_detect(KEY, GPIO.FALLING, bouncetime=300)
	state = GPIO.input(KEY)
	times = 0
	
	while(True):
		if GPIO.event_detected(KEY):
			print("button pressed")
			ledsts = GPIO.input(LED)
			if ledsts == 1:
				GPIO.output(LED, GPIO.LOW)
			else:
				GPIO.output(LED, GPIO.HIGH)
		
except KeyboardInterrupt:
	pass

finally:
	print('Program End!')
	GPIO.cleanup()

	
