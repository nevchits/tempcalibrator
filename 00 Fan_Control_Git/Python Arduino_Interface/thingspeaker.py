import sys
from time import sleep
from urllib.request import urlopen


#temperature = 0
#PID = 0

class dataUpdater():
    #temperature = 0
    #PID = 0

    def setData(temp,pid):
        temperature = temp
        PID = pid
    
    def sendData(temperature,PID):
        # baseURL = 'http://api.thingspeak.com/update?api_key=KRP150IRYKRPKMQ9&field1='
        baseURL = 'https://api.thingspeak.com/update?api_key=KRP150IRYKRPKMQ9&field1={}&field2={}'
        
        newRequest = baseURL.format(temperature,PID)
        print (newRequest)

        f = urlopen(newRequest)
        f.read()
        f.close()
        # sleep(5)
        print ("Data Sent Successfully")




