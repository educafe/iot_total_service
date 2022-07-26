#coding: utf-8

import RPi.GPIO as GPIO
import time

#GPIO.setmode(GPIO.BOARD)
#LED=12
GPIO.setmode(GPIO.BCM)
LED=18

GPIO.setup(LED, GPIO.OUT, initial=GPIO.LOW)
try:
	while(True):
		GPIO.output(LED, GPIO.HIGH)
		time.sleep(0.5)
		GPIO.output(LED, GPIO.LOW)
		time.sleep(0.5)
except KeyboardInterrupt:
	# pass
	GPIO.output(LED, GPIO.LOW)

finally:
	print('Program End!')

GPIO.cleanup()
print('GPIO Cleaned!')
