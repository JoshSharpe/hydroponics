import requests
import config
from abc import ABC, abstractmethod

class Request(ABC):

    def __init__(self, method, path):
        self.method = method
        self.path = path
        self.header = ""
        self.body = ""
        self.responseHeaders = ""
        self.statusCode = 500
        self.responseBody = ""

        self.setHeader()
    
    def setHeader(self):
        self.header = "User-Agent: HydroponicPi\r\nContent-Type: application/json"

    def sendRequest(self, client):
        self.setBody()
        url = config.getHostname() + self.path
        r = requests.request(method=self.method, url=url, headers=self.header, json=self.body)
        self.statusCode = r.status_code
        self.responseHeaders = r.headers
        self.responseBody = r.json()

    @abstractmethod
    def setBody(self):
        return None
