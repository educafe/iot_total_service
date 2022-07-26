import sys
import binascii
import struct
import time
from bluepy.btle import UUID, Peripheral

# led_service_uuid = UUID(0xA000)
# led_char_uuid = UUID(0xA001)
led_service_uuid = "0000ffe0-0000-1000-8000-00805f9b34fb"		#HM10 primary service
led_char_uuid = "0000ffe1-0000-1000-8000-00805f9b34fb"			#HM10 characteristics

if len(sys.argv) != 2:
  print "Fatal, must pass device address:", sys.argv[0], "<device address="">"
  quit()

p = Peripheral(sys.argv[1], "public")
# p = Peripheral(sys.argv[1], "random")
LedService=p.getServiceByUUID(led_service_uuid)

try:
    ch = LedService.getCharacteristics(led_char_uuid)[0]
    while 1:
     	ch.write(struct.pack('<B', 0x31));
      	print ("Led2 on")
     	time.sleep(1)
       	ch.write(struct.pack('<B', 0x30));
    	print ("Led2 off")
       	time.sleep(1)
except KeyboardInterrupt:
	ch.write(struct.pack('<B', 0x30));
finally:
    p.disconnect()
	
# sudo python writeLed2.py <HM10 device address>
