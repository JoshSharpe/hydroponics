import time

class Switch:

    def __init__(self, pin, durationOn, durationOff, timeCreated):
        self.isOn = False
        self.pin = pin
        self.durationOn = durationOn
        self.durationOff = durationOff
        self.lastTriggerTime = timeCreated

    def checkTrigger(self, currentTime):
        timeElapsed = currentTime - self.lastTriggerTime
        print("currentTime: ", currentTime)
        print("timeElapsed: ", timeElapsed)
        print("self.durationOn: ", self.durationOn)

        if (self.isOn and timeElapsed > self.durationOn) \
            or (not self.isOn and timeElapsed > self.durationOff):

            self.trigger()
            self.lastTriggerTime = currentTime
            return True
        
        # if not self.isOn and timeElapsed > self.durationOff:
        #     self.trigger()
        #     return True

        return False

    def trigger(self):
        self.pin.toggle()
        print("Turning pump on/off")
        self.isOn = not self.isOn

