import sys
import tty
import termios
from time import sleep
import select
import numpy


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
			ready, _, _ = select.select([sys.stdin], [], [], .5) #Edited, to allow longer input window.
			if ready:
				byte = ord( sys.stdin.read(1) ) # read 1 byte
				self.bytes[self.lengthOflastChar] = byte
				self.lengthOflastChar += 1 

			#if( byte != 27 ):
			#	return self.bytes, self.lengthOflastChar
				
			#ready, _, _ = select.select([sys.stdin], [], [], 1)
			if ready:
				byte = ord( sys.stdin.read(1) ) # read 2 byte
				self.bytes[ self.lengthOflastChar ] = byte
				self.lengthOflastChar += 1 
			
			if( byte == 27 ): # exit
				return self.bytes, self.lengthOflastChar

			#ready, _, _ = select.select([sys.stdin], [], [], 0)
			if ready:
				byte = ord( sys.stdin.read(1) ) # read 3 byte
				self.bytes[ self.lengthOflastChar ] = byte
				self.lengthOflastChar += 1
			
			# '\x1b' - (dec 27) - special sequence - escape char
			while( byte > 47 and byte < 58 or byte == 59 ): # 48-58 '0'-'9' or ';'
				ready, _, _ = select.select([sys.stdin], [], [], 0)
				if ready:
					byte = ord( sys.stdin.read(1) ) # read 1 byte
					self.bytes[ self.lengthOflastChar ] = byte
					self.lengthOflastChar += 1
		

		except Exception as e :
			pass
			#print("Keyboard reading problem:", e)
		
		return self.bytes, self.lengthOflastChar
	
	def cleanUp(self):
		termios.tcsetattr(self.fd, termios.TCSADRAIN, self.oldSettings)
		

myKeyboard = Keyboard()
myKeyboard.initiation()
import RPi.GPIO as GPIO
from time import sleep
GPIO.setmode(GPIO.BCM)
outPin1 = 27
inPin = 22
GPIO.setup(outPin1,GPIO.OUT)
GPIO.setup(inPin,GPIO.IN,pull_up_down=GPIO.PUD_UP)
PWM=GPIO.PWM(outPin1,100) #This should set frequency to 100HZ on setup
answ =""
count = 0
print("-- Press 'UP arrow' to turn on the LED, 'DOWN arrow' to turn it off, or 'ESC' twice to quit. -- \r")

brightness = numpy.logspace(0, 2, num=10)
while answ != 'q':
	inp, l = myKeyboard.readKey()
	state = GPIO.input(inPin)
	state = 0
	if ((inp[0] == 27 and inp[1] == 27)):
		print("Exiting")
		break
	
	elif (state == 0):
		PWM.start(brightness[count])
		count += 1 
		if count > 9:
			count = count % 10
			PWM.stop()
		
	else:
		state = 0
		sleep(.1)
		pass

PWM.stop()
GPIO.cleanup()
myKeyboard.cleanUp()
