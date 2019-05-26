#include "Request.h"

class SwitchRequest: public Request {
    private:
        SwitchType type;
        bool isTurningOn;
        void setBody ();

    public:
        SwitchRequest(String method, SwitchType type, bool isTurningOn);
};

enum SwitchType {
    WaterPump, 
    Lights
};
