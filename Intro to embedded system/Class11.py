import sys
import tty
import termios
from time import sleep
import select


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
			ready, _, _ = select.select([sys.stdin], [], [], 0)
			if ready:
				byte = ord( sys.stdin.read(1) ) # read 1 byte
				self.bytes[self.lengthOflastChar] = byte
				self.lengthOflastChar += 1 

			if( byte != 27 ):
				return self.bytes, self.lengthOflastChar
			
			ready, _, _ = select.select([sys.stdin], [], [], 0)
			if ready:
				byte = ord( sys.stdin.read(1) ) # read 2 byte
				self.bytes[ self.lengthOflastChar ] = byte
				self.lengthOflastChar += 1 
			
			if( byte == 27 ): # exit
				return self.bytes, self.lengthOflastChar

			ready, _, _ = select.select([sys.stdin], [], [], 0)
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
outPin2 = 22
inPin = 17
GPIO.setup(outPin1,GPIO.OUT)
GPIO.setup(outPin2,GPIO.OUT)
GPIO.setup(inPin,GPIO.IN,pull_up_down=GPIO.PUD_DOWN)
answ =""
flag = 0
print("-- Press 'UP arrow' to turn on the LED, 'DOWN arrow' to turn it off, or 'ESC' twice to quit. -- \r")
while answ != 'q':
	inp, l = myKeyboard.readKey()
	state = GPIO.input(inPin)
	if (inp[0] ==27):
		sleep(.5)
		if(inp[0] == 27 and inp[0] == 27):
			print('Exiting program.\r')
			myKeyboard.cleanUp()
			ans = 'q'
			break
	
	elif(state==1):
		if flag == 0:
			GPIO.output(outPin2,False)
			GPIO.output(outPin1,True)
			print("RED LED OFF / YELLOW LED ON\r")
			sleep(.1)
			flag =1
		else:
			GPIO.output(outPin1,False)
			GPIO.output(outPin2,True)
			print("RED LED ON / YELLOW LED OFF\r")
			sleep(.1)
			flag =0
	
	else:
		sleep(.1)
		pass

GPIO.cleanup()
myKeyboard.cleanUp()
