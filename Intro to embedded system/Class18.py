import sys
import tty
import termios
from time import sleep
import select
import numpy
import threading


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

button_state = True  # Initial state (pull-up)
led_state = True
global stop_event
stop_event = threading.Event()  # Event to stop the thread
# Start monitoring in a separate daemon thread

import RPi.GPIO as GPIO
import time

def monitor_input():
	"""Monitors input changes in a separate thread."""
	#GPIO.setmode(GPIO.BCM)  # BCM mode 
	inPin = 17
	GPIO.setup(inPin,GPIO.IN,pull_up_down=GPIO.PUD_UP)
	GPIO.add_event_detect(inPin, GPIO.BOTH,bouncetime=1)

	global channel
	channel = 0 # Red = 0, Green = 1, Blue = 2
	global button_state, led_state
	while not stop_event.is_set():
		try:
			#new_state = GPIO.input(inPin)
			if GPIO.event_detected(inPin):  # Falling edge detected
				print("\rSwitch pressed!")
				channel = (channel + 1) % 3
				led_state = not led_state
			#if GPIO.event_detected(inPin)  and button_state == 1:  # Still high, do nothing
			#	pass
			#button_state = new_state
			#sleep(0.1)  # Debounce (basic implementation)
		except EOFError:  # EOF or Ctrl+C
			break	

def monitor_keyboard():
	myKeyboard = Keyboard()
	myKeyboard.initiation()
	global keypressed
	brightness = numpy.logspace(0, 2, num=10)
	step = 0 

	outPinRed = 20
	outPinGreen = 16
	outPinBlue = 21
	outPins = [20,16,21]
	GPIO.setup(outPins,GPIO.OUT)
	PWMR=GPIO.PWM(outPinRed,100) #This should set frequency to 100HZ on setup
	PWMB=GPIO.PWM(outPinBlue,100)
	PWMG=GPIO.PWM(outPinGreen,100)
	PWMS = [PWMR,PWMB,PWMG]

	while not stop_event.is_set():
		try:
			inp, l = myKeyboard.readKey()
			if ((inp[0] == 27 and inp[1] == 27)):
				stop_event.set()
				myKeyboard.cleanUp()
				break
			elif ((inp[1] == 91 and inp[2] == 65)):
				if step < 10:
					step = (step + 1)
				else:
					pass
					PWMS[channel].start(float(brightness[step]))
			elif ((inp[1] == 91 and inp[2] == 66)):
				if step > 0:
					step = (step - 1)
			elif step == 0:
				PWMS[channel].start(float(0))
			else:
				PWMS[channel].start(float(brightness[step]))
				pass

		except EOFError:  # EOF or Ctrl+C
			break
	myKeyboard.cleanUp()
	
	for pwm in PWMS:
		pwm.stop()
	GPIO.cleanup()

	# Channel change block
	
def main():
	myKeyboard = Keyboard()
	myKeyboard.initiation()
	GPIO.setmode(GPIO.BCM)

	while stop_event.is_set() != True:
		answ =""
		#now = False
		print("-- Press 'UP arrow' to turn on the LED, 'DOWN arrow' to turn it off, or 'ESC' twice to quit. --/r")
		brightness = numpy.logspace(0, 2, num=10)
		input_thread = threading.Thread(target=monitor_input, daemon=True)
		input_thread.start()
		keyb_thread = threading.Thread(target=monitor_keyboard, daemon=True)
		keyb_thread.start()

		try:
			while stop_event.is_set() != True:
				sleep(.1)
				# if (button_state == 0):
				# 	PWMR.start(float(brightness[count]))
				# 	PWMB.start(float(brightness[count]))
				# 	PWMG.start(float(brightness[count]))
				# 	count += 1 
				# 	count = count % 10
				# else:
				# 	sleep(.1)
				# 	pass	
		except KeyboardInterrupt:
			stop_event.set()  # Stop the thread
			GPIO.cleanup()  # Clean up GPIO resources
			print("Exiting.")
		

main()



