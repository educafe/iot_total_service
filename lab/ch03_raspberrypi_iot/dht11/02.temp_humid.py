import RPi.GPIO as GPIO
import dht11
import time
import datetime

# initialize GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.cleanup()
DHTPIN=18

# read data using dht_pin
device = dht11.DHT11(DHTPIN)

while True:
	ret = device.read()
	if ret.is_valid():
		print("Measured at : " + str(datetime.datetime.now()))
		# print("Temperature: %d C, Humidity: %d %%" % (ret.temperature,ret.humidity))
		print("Humidity = {} %; Temperature = {} C".format(ret.humidity,ret.temperature))

	time.sleep(1)