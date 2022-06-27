#include "System/System.h"

RobotSystem* robotSystem;

class Robot : public RobotSystem{
public:
    void RobotPeriodic() override{
        Serial.println("Edited RobotPeriodic()");
    }
};
Robot* robot;

void setup() {
    
}


void loop() {
    
}
