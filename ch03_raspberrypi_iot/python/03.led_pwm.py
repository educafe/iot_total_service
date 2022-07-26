#coding: utf-8

import RPi.GPIO as GPIO
import time

#GPIO.setmode(GPIO.BOARD)
#LED = 12

GPIO.setmode(GPIO.BCM)
LED = 18
GPIO.setup(LED, GPIO.OUT, initial=GPIO.LOW)
p = GPIO.PWM(LED, 100)

try:
	p.start(0)
	while(True):
		# for val in dc:
		for val in range(0,100):
			p.ChangeDutyCycle(val)
			time.sleep(0.1)
		for val in range(100,0):
			p.ChangeDutyCycle(val)
			time.sleep(0.1)
		time.sleep(3)

except KeyboardInterrupt:
	# pass
	GPIO.output(LED, GPIO.LOW)
finally:
	print('Program End!')
	p.start(0)
	GPIO.cleanup()

	
