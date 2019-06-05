import json

def readConfig():
    with open('config.json') as config_file:
        data = json.load(config_file)
        return data

configuration = readConfig()


def getWifiUsername():
        return configuration["wifi_username"]

def getWifiPassword():
        return configuration["wifi_password"]

def getHostname():
        return configuration["hostname"]

def getPort():
        return configuration["port"]