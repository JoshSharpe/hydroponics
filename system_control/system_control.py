import gpiozero
import switch
import time

lightsPin = gpiozero.DigitalOutputDevice(17)
lightSwitch = switch.Switch(lightsPin, getSecondsFromMinutes(30), getSecondsFromMinutes(90))

pumpPin = gpiozero.DigitalOutputDevice(18)
pumpSwitch = switch.Switch(pumpPin, getSecondsFromMinutes(30), getSecondsFromMinutes(90))

def mainLoop():
    while True:
        currentTime = time.time()
        lightSwitch.checkTrigger(currentTime)
        pumpSwitch.checkTrigger(currentTime)



def getSecondsFromMinutes(minutes):
    return minutes * 60