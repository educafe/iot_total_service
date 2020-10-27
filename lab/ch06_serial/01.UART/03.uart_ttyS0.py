import serial
import time

# ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
ser = serial.Serial('/dev/ttyS0', 9600, timeout=1)
ser.close()
ser.open()

try:
  while 1:
    ser.write('1')    
    rxdata = ser.readline();
    print(rxdata);
    time.sleep(2)
    ser.write('0')    
    rxdata = ser.readline();
    print(rxdata);
    time.sleep(2)

except KeyboardInterrupt:
  ser.close()
