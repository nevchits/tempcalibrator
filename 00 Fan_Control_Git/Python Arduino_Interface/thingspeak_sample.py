'''
This code takes values calulated and puts them into a variable called f which consists of an baseURL which is specific for your project
since it is defined by the api_key. The variable f is the link including the new value that inserts a new measurment point to your 
thingspeak channel. the f.read() command opens this link and the f.close command closes it. The variable that is transmitted can be
changed as you want to. In this case it calculates Fibonnaci Numbers.
'''

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




