import serial

nanoSerial = serial.Serial

nanoSerial.baudrate = 9600;
nanoSerial.port = "/dev/ttyUSB0"

try:
    nanoSerial.open()
    
    while (1):
        serialOutput = nanoSerial.read_until("5")
        print  (serialOutput)

except:
    print ("Zvaramba")

