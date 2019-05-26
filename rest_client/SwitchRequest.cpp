
#include "SwitchRequest.h"

SwitchRequest::SwitchRequest(String method, SwitchType type, bool isTurningOn) :
    type(type),
    isTurningOn(isTurningOn),
    Request(method, "/api/plants/logs/switch")
{}


void SwitchRequest::setBody() {
    String type = this->type == SwitchType::WaterPump ? "water_pump" : "led";

    this->body = "{\"log_type\": " + type + ", \"turning_on\": " + isTurningOn + ", \"turning_off: \"" + !isTurningOn + "}";
}