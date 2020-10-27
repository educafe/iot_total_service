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
#GPIO.setup(KEY, GPIO.IN)
GPIO.setup(KEY, GPIO.IN, pull_up_down=GPIO.PUD_UP)

try:
	while(True):
		key_in = GPIO.input(KEY)
		if key_in==0:
			GPIO.output(LED, GPIO.HIGH)
		else:
			GPIO.output(LED, GPIO.LOW)
		
except KeyboardInterrupt:
	# pass
	GPIO.output(LED, GPIO.LOW)
finally:
	print('Program End!')
	GPIO.cleanup()

	
