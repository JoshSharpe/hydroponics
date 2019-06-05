

class Switch:

    def __init__(self, pin, durationOn, durationOff):
        self.isOn = False
        self.pin = pin
        self.durationOn = durationOn
        self.durationOff = durationOff
        self.lastTriggerTime = 0

    def checkTrigger(self, currentTime):
        timeElapsed = currentTime - self.lastTriggerTime

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
        self.isOn = not self.isOn

