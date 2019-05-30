#LIBRARIES
#Firebase Libraries
from firebase import firebase
import Adafruit_DHT

#NRF24 wireless sensor libraries
import RPi.GPIO as GPIO
from lib_nrf24 import NRF24
import time
import spidev
#--------------------------------------------------------------------------
#SETUP
#Firebase connection
firebase = firebase.FirebaseApplication('https://cse408shademaker.firebaseio.com/', None)

#NRF24 Setup
GPIO.setmode(GPIO.BCM)

pipes = [[0xE8, 0xE8, 0xF0, 0xF0, 0xE1], [0xF0, 0xF0, 0xF0, 0xF0, 0xE1]]

radio = NRF24(GPIO, spidev.SpiDev())
radio.begin(0, 17)

radio.setPayloadSize(32)
radio.setChannel(0x76)
radio.setDataRate(NRF24.BR_2MBPS)
radio.setPALevel(NRF24.PA_MIN)

radio.setAutoAck(True)
radio.enableDynamicPayloads()
radio.enableAckPayload()

radio.openWritingPipe(pipes[0])
radio.openReadingPipe(1, pipes[1])
radio.printDetails()

#---------------------------------------------------------
#SYSTEM LOOP
while True:
    #Recieving Data from Firebase
    BlindStatus = firebase.get('/Status', None)
    print ("Firebase Status:", BlindStatus)
    
    #---------------------------------------
    #NRF24 Recieving Data from Arduino
    string = ""
    timedelay = 0
    radio.startListening()
    while not radio.available(0):
        time.sleep(.01)
        timedelay +=1
        if timedelay >= 200:
            print("Timed out")
            break
    if radio.available():
        receivedMessage = []
        radio.read(receivedMessage, radio.getDynamicPayloadSize())
        print("Received: {}".format(receivedMessage))

        print("Translating our received Message into unicode characters...")

        for n in receivedMessage:
            if (n >= 32 and n <= 126):
                string += chr(n)
        print("Our received message decodes to: {}".format(string))
    radio.stopListening()
    
    #-----------------------------------
    #NRF24 Sending Data to Arduino
    message = str(BlindStatus)#converting int to char list to send
    message = list(message)
    while len(message) <= 16:
        message.append(0)
        
    #start = time.time()
    radio.write(message)
    print("Sent the message: {}".format(message))
    time.sleep(.5)
    
    #---------------------------------------
    #Sending Data from Arduino to Firebase
    if string == "open":
        firebase.put('user','LightValue', 1)
    elif string == "close":
        firebase.put('user','LightValue', 0)
