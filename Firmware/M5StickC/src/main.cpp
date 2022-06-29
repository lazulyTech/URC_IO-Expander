#include "System/System.h"

bool urc::test = false;

class Robot : public RobotSystem{
public:
    using RobotSystem::RobotSystem;
    void RobotPeriodic() override{
        Serial.println("Edited RobotPeriodic()");
    }
    void TestPeriodic() override{
        M5.Lcd.fillScreen(M5.Lcd.color565(0x42, 0x6a, 0xb3));
    }
    void DisabledPeriodic() override{
        M5.Lcd.fillScreen(RED);
    }
    void AutonomousPeriodic() override{
        M5.Lcd.fillScreen(GREEN);
    }
    void TeleopPeriodic() override{
        M5.Lcd.fillScreen(BLUE);
    }
};
RobotSystem* robot;
System* _system;

void setup() {
    robot = new Robot(urc::dio, urc::pwm, urc::ain, urc::motor);
    _system = new System(urc::espNow, urc::dio, urc::dio_internal, 
                            urc::pwm, urc::ain, urc::motor, robot);
    _system->SystemInit();
}


void loop() {
    Serial.print("Mode ");
    Serial.println(urc::myData.mode);
    // Serial.print("Null Addr ");
    // int* a = NULL;
    // Serial.printf("%p\n", a);
    _system->SystemPeriodic();
    delay(10);
}
