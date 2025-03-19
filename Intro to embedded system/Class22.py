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
import pigpio
import time
# pi = pigpio.pi()
# PIN = 12
# pi.set_PWM_frequency(PIN, 50)
# pi.set_PWM_dutycycle(PIN, int(255 * .99) ) # 1 byte
# pi.set_PWM_dutycycle(PIN, 0)
# pi.stop()
def monitor_input():
	"""Monitors input changes in a separate thread."""
	#GPIO.setmode(GPIO.BCM)  # BCM mode 
	inPin = 21
	GPIO.setup(inPin,GPIO.IN,pull_up_down=GPIO.PUD_UP)
	GPIO.add_event_detect(inPin,GPIO.FALLING,bouncetime=200)

	global channel
	channel = 0 # Red = 0, Green = 1, Blue = 2
	global button_state, led_state
	while not stop_event.is_set():
		try:
			#new_state = GPIO.input(inPin)
			if GPIO.event_detected(inPin):  # Falling edge detected
				#print("\rSwitch pressed!")
				channel = (channel + 1) % 4  #Modulo by 4 in order to make sure that the index remains withen the bounds of the list
				#led_state = not led_state
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
	brightness = brightness[::-1]


	#outPinRed = 20
	#outPinGreen = 16
	#OutPin= 20
	#GPIO.setup(OutPin,GPIO.OUT,)

	while not stop_event.is_set():

		try:
			inp, l = myKeyboard.readKey()
			
			if ((inp[0] == 27 and inp[1] == 27)):
				stop_event.set()
				myKeyboard.cleanUp()
				break
			######################################### Old keyboard detection code for arrow keys
			# elif ((inp[1] == 91 and inp[2] == 65)):
			# 	if PWMSteps[channel] < 9:
			# 		PWMSteps[channel] = (PWMSteps[channel]+ 1)
			# 		PWMS[channel].start(brightness[PWMSteps[channel]])
			# 	else:
			# 		pass

			# elif ((inp[1] == 91 and inp[2] == 66)):
			# 	if PWMSteps[channel] > 0:
			# 		PWMSteps[channel] = (PWMSteps[channel] - 1)
			# 		PWMS[channel].start(brightness[PWMSteps[channel]])
			#############################################################
			else:
				sleep(.2)


		except EOFError:  # EOF or Ctrl+C
			break
	myKeyboard.cleanUp()
	# for pwm in PWMS:
	# 	pwm.stop()
	GPIO.cleanup()

	# Channel change block
	
def main():
	myKeyboard = Keyboard()
	myKeyboard.initiation()
	GPIO.setmode(GPIO.BCM)
	OutPin= 20
	GPIO.setup(OutPin,GPIO.OUT)
	OutPWM = GPIO.PWM(OutPin,150)
	timing = [.1,.01,.001,.0001]

	while stop_event.is_set() != True:
		answ =""
		print("-- Press the switch to change the speed of the siren. Press ESC to exit. --\r")
		brightness = numpy.logspace(0, 2, num=10)  
		input_thread = threading.Thread(target=monitor_input, daemon=True)
		input_thread.start()
		keyb_thread = threading.Thread(target=monitor_keyboard, daemon=True)
		keyb_thread.start()
		OutPWM.start(50);


		try:
			while stop_event.is_set() != True: 
				for freq in range(150,2000): # Increasing from 150 to 1999 inclusive - 2000 is in the decrementing loop
					OutPWM.ChangeFrequency(freq)
				# 	print(f"{freq}\r") - Debug code
				for freq in range(2000,150,-1): # Starts decrementing including 2000 to 149
					OutPWM.ChangeFrequency(freq)
					# print(f"{freq}\r") #- Debug code


		except KeyboardInterrupt:
			stop_event.set()  # Stop the thread
			#OutPWM.stop()
			GPIO.cleanup()  # Clean up GPIO resources
			print("Exiting.")
		
main()
