# import modules
import os
import RPi.GPIO as GPIO
from gpiozero import DistanceSensor
from time import sleep

# set pins for the ultrasonic sensor here
ultrasonicTrigger = 20
ultrasonicEcho = 21

# the maximum distance (in centimeter) required to trigger the program to publish event
triggerDistance = 80

# setting up GPIO and the sensor
GPIO.setmode(GPIO.BCM)
GPIO.setup(ultrasonicTrigger, GPIO.OUT)
sensor = DistanceSensor(trigger = ultrasonicTrigger, echo = ultrasonicEcho)

# login to Particle account
os.system('particle login')

try:
    # infinite loop. breaks if the user presses ctrl + C
	while True:
        # delay of 3.5 seconds between data read and event publish
		sleep(3.5)
        
        # read distance data with the ultrasonic sensor, convert it to centimeter
		distance = sensor.distance
		distance = round(sensor.distance, 1)
		centimeter = distance * 100
		print(centimeter)
        
        # if the distance is less than the defined triggerDistance, the program will publish a public Particle event
		if centimeter < triggerDistance:
            # publish a public event "sensors_trigger" with value "UltrasonicSensorTriggered"
			os.system('particle publish --public "sensors_trigger" "UltrasonicSensorTriggered"')
except KeyboardInterrupt:
    # when the user presses ctrl + C, this except block will catch the exception thrown
    # will do nothing
	pass

# cleanup the GPIO pins once this program has ended
GPIO.cleanup()
