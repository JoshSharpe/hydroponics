import gpiozero
import switch
import time
import switch_request

lightPinNumber = 23
pumpPinNumber = 24
lightsSecondsOn = 5
lightsSecondsOff = 500000
pumpSecondsOn = 5000000
pumpSecondsOff = 50000000

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

        isTriggered = lightSwitch.checkTrigger(currentTime)
        if isTriggered:
                req = switch_request.SwitchRequest("POST", "led", lightSwitch.isOn)
                req.sendRequest()

        isTriggered = pumpSwitch.checkTrigger(currentTime)
        if isTriggered:
                req = switch_request.SwitchRequest("POST", "water_pump", lightSwitch.isOn)
                req.sendRequest()
                
        time.sleep(1)

if __name__ == "__main__":
    main()
