#Student: Yenshae Fan
#CSCI 255 Spring 2025
#Assignment: Class05.py - LED Control with User Input:

#I acknowledge that I have worked on this assignment independently, except where explicitly noted and referenced. Any collaboration or use of external resources has been #properly cited. I am fully aware of the consequences of academic dishonesty and agree to abide by the university's academic integrity policy. I understand the importance the #consequences of plagiarism.

import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
outPin = 17
GPIO.setup(outPin,GPIO.OUT)
GPIO.output(outPin,1)
answ =""
while answ != 'q':
    answ=input("-- Press 'y' to turn on the LED, 'n' to turn it off, or 'q' to quit. -- ")
    match answ:
        case 'y':
            GPIO.output(outPin,1)
        case 'n':
            GPIO.output(outPin,0)
        case 'q':
            break
        case _:
            print('Invalid input please try again')



#GPIO.cleanup()


