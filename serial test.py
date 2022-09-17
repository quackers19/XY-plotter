import serial
import time

arduino = serial.Serial(port='COM5', baudrate=9600, timeout=.2)

def read():
    return arduino.readline().decode('utf-8')


while True:
    print (read())