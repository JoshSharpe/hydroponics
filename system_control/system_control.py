import gpiozero
import switch
import time
import json
from switch_request import SwitchRequest
from flask import Flask
from flask_restful import reqparse, abort, Api, Resource, inputs

app = Flask(__name__)
api = Api(app)

parser = reqparse.RequestParser()
parser.add_argument(SwitchRequest.waterPump)
parser.add_argument(SwitchRequest.lights)

lightPinNumber = 23
pumpPinNumber = 24

currentTime = time.time()
lightsPin = None
# lightsPin = gpiozero.DigitalOutputDevice(lightPinNumber)
lightSwitch = switch.Switch(lightsPin, currentTime)

pumpPin = None
# pumpPin = gpiozero.DigitalOutputDevice(pumpPinNumber)
pumpSwitch = switch.Switch(pumpPin, currentTime)


def getSecondsFromMinutes(minutes):
    return minutes * 60


def getSwitchData():
    data = {}
    data[SwitchRequest.waterPump] = pumpSwitch.isOn
    data[SwitchRequest.lights] = lightSwitch.isOn
    return data


def setSwitchData(jsonData):
    resp = {}
    print("TEST: ", jsonData)
    if SwitchRequest.waterPump in jsonData:
        pumpValue=inputs.boolean(jsonData[SwitchRequest.waterPump])
        pumpSwitch.setSwitch(pumpValue)
        resp[SwitchRequest.waterPump]=pumpValue

    if SwitchRequest.lights in jsonData:
        lightValue=inputs.boolean(jsonData[SwitchRequest.lights])
        lightSwitch.setSwitch(lightValue)
        resp[SwitchRequest.lights]=lightValue

    return resp

class Switches(Resource):
    def get(self):
        return getSwitchData()

    def post(self):
        args=parser.parse_args()
        resp=setSwitchData(args)
        return resp, 201


def main():
    api.add_resource(Switches, '/api/switches')
    app.run(debug=True)


if __name__ == "__main__":
    main()
