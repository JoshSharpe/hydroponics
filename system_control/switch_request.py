import request

class SwitchRequest(request.Request):

    waterPump = "water_pump"
    lights = "lights"

    def __init__(self, method, type, isTurningOn):
        self.type = type
        self.isTurningOn = isTurningOn
        super().__init__(method, "/plants/switches")

    def setBody(self):
        self.body = {"log_type": self.type, "turning_on": self.isTurningOn, "turning_off": not self.isTurningOn}