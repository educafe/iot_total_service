#coding: utf-8

import RPi.GPIO as GPIO
import time

#GPIO.setmode(GPIO.BOARD)
#LED=12

GPIO.setmode(GPIO.BCM)
LED=[[17,18],[18,27],[27,17],[22,18],[23,27],[24,22],[25,23],[4,24],[4,25],\
	[4,25],[25,24],[24,4],[23,25],[22,24],[27,23],[18,22],[17,27],[17,18]]
KEY = 26

def handle(pin):
	# global state
	global times
	# for i in range(1, 100000):
		# pass
	print("button state", int(GPIO.input(pin)))
	if(GPIO.input(pin) != state):
		times += 2
		if times >= 12:
			times = 0
		# print ('button clicked ' + repr(times))
		print ("button clicked ", int(times))

for i in range (0, 8):
	GPIO.setup(LED[i][0], GPIO.OUT, initial=GPIO.LOW)

try:

	GPIO.setup(KEY, GPIO.IN, pull_up_down=GPIO.PUD_UP)
	times = 0
	GPIO.add_event_detect(KEY, GPIO.FALLING, callback=handle, bouncetime=500)
	state = GPIO.input(KEY)
	
	while(True):
		# for val in range(0,18):
		for val in range (len(LED)):
			GPIO.output(LED[val][0], GPIO.HIGH)
			GPIO.output(LED[val][1], GPIO.LOW)
			time.sleep(0.01*times)
			
except KeyboardInterrupt:
	pass

finally:
	print('Program End!')
	GPIO.cleanup()
