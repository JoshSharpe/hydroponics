import gpiozero
import switch
import time

lightPinNumber = 23
pumpPinNumber = 24
lightsSecondsOn = 5
lightsSecondsOff = 5
pumpSecondsOn = 5
pumpSecondsOff = 5

def getSecondsFromMinutes(minutes):
    return minutes * 60

def main():
    currentTime = time.time()
    lightsPin = gpiozero.DigitalOutputDevice(lightPinNumber)
    lightSwitch = switch.Switch(lightsPin, lightsSecondsOn, lightsSecondsOff, currentTime)

    pumpPin = gpiozero.DigitalOutputDevice(pumpPinNumber)
    pumpSwitch = switch.Switch(pumpPin, pumpSecondsOn, pumpSecondsOff, currentTime)
    
    while True:
        currentTime = time.time()
        lightSwitch.checkTrigger(currentTime)
        pumpSwitch.checkTrigger(currentTime)
        time.sleep(1)

if __name__ == "__main__":
    main()
