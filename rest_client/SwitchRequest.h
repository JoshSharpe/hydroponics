#ifndef request_h
#define request_h
#include "Request.h"
#endif

enum SwitchType {
    WaterPump, 
    Lights
};

class SwitchRequest: public Request {
    private:
        SwitchType type;
        bool isTurningOn;
        void setBody ();

    public:
        SwitchRequest(String method, SwitchType type, bool isTurningOn);
};
