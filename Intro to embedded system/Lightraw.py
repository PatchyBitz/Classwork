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
GPIO.setmode(GPIO.BCM)
outPin = 17
GPIO.setup(outPin,GPIO.OUT)
GPIO.output(outPin,1)
answ =""
while answ != 'q':
	print("-- Press 'UP arrow' to turn on the LED, 'DOWN arrow' to turn it off, or 'ESC' twice to quit. -- ")
	inp, l = myKeyboard.readKey()
	if (inp[0] == 27 and inp[2] == 65):

		GPIO.output(outPin,1)
	elif(inp[0] == 27 and inp[2] == 66):

		GPIO.output(outPin,0)
	elif(inp[0] == 27 and inp[1] == 27):
		print('Exiting...')
		break
	else:
		print("Invalid Character please try again")

GPIO.cleanup()


