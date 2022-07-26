#!/usr/bin/env python
import sys, time
from bledevice import scanble, BLEDevice

if len(sys.argv) != 2:
    print "Usage: ./01.led-onoff-notify.py <ble address>"
    print "Scaned devices are as follows:"
    print scanble()
    sys.exit(1)

hm10 = BLEDevice(sys.argv[1])
try:
	while True:
		vh=hm10.getvaluehandle("ffe1")
		# hm10.writecmd(vh, "test\r\n".encode('hex'))
		hm10.writecmd(vh, "1".encode('hex'))
		data = hm10.notify()
		if data is not None:
			print "Received: ", data
		time.sleep(1)
		hm10.writecmd(vh, "0".encode('hex'))
		data = hm10.notify()
		if data is not None:
			print "Received: ", data
		time.sleep(1)
except KeyboardInterrupt:
	hm10.writecmd(vh, "0\r\n".encode('hex'))
finally:
    pass
	

