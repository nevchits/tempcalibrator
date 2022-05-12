from time import sleep
import serial
from thingspeak_sample import dataUpdater
import thingspeaker

serialOutputString = ""
temp,pid = 0,0

nanoSerial = serial.Serial("/dev/ttyUSB0",9600)
myupdater = dataUpdater

# nanoSerial.baudrate = 9600;
# nanoSerial.port = "/dev/ttyUSB0"

# nanoSerial.open()

def sendtoDatabase (temperature, PID):
    # placeholder
    pass

def sendToThingspeak(temperature, PID):
    # make sure you have a pair of data greater than 0
    if (temperature == 0 or PID == 0):
        print ("not sufficient data. Wait till you have a full pair.")
    else:
        myupdater.sendData(temperature,PID)
    
    sleep(5)

while (1):
    serialOutput = nanoSerial.readline()
    
    try:
        serialOutputString = serialOutput.decode()
    except UnicodeDecodeError as e:
        print("Unicode Decode Error:\n " + str(e))
    
    # print  (serialOutputString)

    if (serialOutputString.__contains__("Input")):
        inputVal = serialOutputString.split("-->")
        temp = inputVal[len(inputVal)-1]
        temp = temp.strip()
        temp = temp.strip('\r')
        temp = temp.strip('\r')
        temp = temp.strip('\n')
        print("Temp = " + temp)


    # getting the PID output using this format: "Calculated output --> 148.50\n"
    if (serialOutputString.__contains__("Calculated")):
        inputVal = serialOutputString.split("-->")
        pid = inputVal[len(inputVal)-1]
        pid = pid.strip()
        pid = pid.strip('\r')
        pid = pid.strip('\n')
        print("PID output = " + pid)

    # let's breathe, although we'll need to breathe after every 2 lines:
    # time.sleep(5)
    sendToThingspeak(temp,pid)

nanoSerial.close()
