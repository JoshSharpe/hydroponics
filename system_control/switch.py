import time

class Switch:

    def __init__(self, pin, timeCreated):
        self.isOn = False
        self.pin = pin
        self.lastTriggerTime = timeCreated
        self.timeCreated = timeCreated

    def setSwitch(self, isOn):
        if isOn:
            self.turnOn()
            return
        
        self.turnOff()

    def trigger(self):
        self.pin.toggle()
        self.isOn = not self.isOn

    def turnOn(self):
        self.isOn = True
        # self.pin.on()
        print("Turning pump on.")
        self.lastTriggerTime = time.time()

    def turnOff(self):
        self.isOn = False
        print("Turning pump off.")
        # self.pin.off()
        self.lastTriggerTime = time.time()

