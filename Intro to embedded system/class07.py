#Student: YenShae Fan
#CSCI 255 Spring 2025
#Assignment: LED Control with RAW mode input
#I acknowledge that I have worked on this assignment independently, except where explicitly noted and referenced.
#Any collaboration or use of external resources has been ;properly cited. I am fully aware of the consequences of academic
#dishonesty and agree to abide by the university's academic integrity policy. I understand the importance the consequences of plagiarism.
#Keyboard Class was provided by Professor Jakub Pach for this assignment

import sys
import tty
import termios


repeat = True

class Keyboard:
	'''
		Initialize the keyboard in raw mode by modifying terminal settings.
		Returns:  bool: True if initialization succeeded, False otherwise.
	'''
	def __init__(self):
		self.fd = None
		self.oldSettings = None		
		self.bytes  = [0] * 10 #'\0'
		self.lengthOflastChar = 0

	def initiation(self):
		try:
			self.fd = sys.stdin.fileno()
			self.oldSettings = termios.tcgetattr(self.fd)
			tty.setraw(self.fd)  # raw terminal mode
			return True
		except:
			return False
		
	def readKey(self):

		for i in range(len(self.bytes)):
			self.bytes[i] = 0

		self.lengthOflastChar = 0

		try:
			byte = ord( sys.stdin.read(1) ) # read 1 byte
			self.bytes[self.lengthOflastChar] = byte
			self.lengthOflastChar += 1 

			if( byte != 27 ):
				return self.bytes, self.lengthOflastChar
			
			byte = ord( sys.stdin.read(1) ) # read 2 byte
			self.bytes[ self.lengthOflastChar ] = byte
			self.lengthOflastChar += 1 
			
			if( byte == 27 ): # exit
				return self.bytes, self.lengthOflastChar

			byte = ord( sys.stdin.read(1) ) # read 3 byte
			self.bytes[ self.lengthOflastChar ] = byte
			self.lengthOflastChar += 1
			
			# '\x1b' - (dec 27) - special sequence - escape char
			while( byte > 47 and byte < 58 or byte == 59 ): # 48-58 '0'-'9' or ';'
				byte = ord( sys.stdin.read(1) ) # read 1 byte
				self.bytes[ self.lengthOflastChar ] = byte
				self.lengthOflastChar += 1
			

		except Exception as e :
			print("Keyboard reading problem:", e)
		
		return self.bytes, self.lengthOflastChar
	
	def cleanUp(self):
		termios.tcsetattr(self.fd, termios.TCSADRAIN, self.oldSettings)

myKeyboard = Keyboard()
myKeyboard.initiation()
import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
outPin = 17
GPIO.setup(outPin,GPIO.OUT)
GPIO.output(outPin,1)
answ =""
now = False
print("-- Press 'UP arrow' to turn on the LED, 'DOWN arrow' to turn it off, or 'ESC' twice to quit. -- ")
while answ != 'q':
	inp, l = myKeyboard.readKey()
	if(inp[0] ==27 and inp[2] == 65 and now == True or inp[0] == 27 and inp[2] == 66 and now == False):
		time.sleep(1)				#Technically not necassary, but should slow down the amount of reads being conducted. 
		pass
	else:
		print("-- Press 'UP arrow' to turn on the LED, 'DOWN arrow' to turn it off, or 'ESC' twice to quit. -- ")
		if (inp[0] == 27 and inp[2] == 65):
			if (now == False):
				now=True
				GPIO.output(outPin,1)
			else:
				pass
		elif(inp[0] == 27 and inp[2] == 66):
			if (now == True):
				now=False
				GPIO.output(outPin,0)
			else:
				pass
		elif(inp[0] == 27 and inp[1] == 27):
			print('Exiting...')
			break
		else:
			print("Invalid Character please try again")

GPIO.cleanup()


