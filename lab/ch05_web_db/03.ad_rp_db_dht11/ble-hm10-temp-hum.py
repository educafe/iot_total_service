#!/usr/bin/env python
import sys, time
from bledevice import scanble, BLEDevice
import mysql.connector
import time

if len(sys.argv) != 2:
    print "Usage: python blecomm.py <ble address>"
    print "Scan devices are as follows:"
    print scanble(timeout=3)
    sys.exit(1)

mydb = mysql.connector.connect(
  host="localhost",
  user="root",
  passwd="root",
  database="mydb1"
)		

mycursor = mydb.cursor()
hm10 = BLEDevice(sys.argv[1])
try:
	while True:
		vh=hm10.getvaluehandle("ffe1")
		# hm10.writecmd(vh, "test\r\n".encode('hex'))
		data = hm10.notify()
		if data is not None:
			print "Received: ", data
			hm10.writecmd(vh, "1".encode('hex'))
			sql = "INSERT INTO dht11 (temperature_humidity, created) VALUES (%s, %s)"
			val = (data, time.localtime(time.time()))
			mycursor.execute(sql, val)
			mydb.commit()
except KeyboardInterrupt:
	hm10.writecmd(vh, "0\r\n".encode('hex'))
finally:
    pass
	

