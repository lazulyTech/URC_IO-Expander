#include "System/System.h"

bool urc::test = true;
int urc::teamNumber = 0;

class Robot : public RobotSystem{
private:
    int count = 0;
public:
    using RobotSystem::RobotSystem;
    void RobotInit() override{
        for(int i = 0; i < 16; i++){
            dio->pinMode(i, OUTPUT);
        }
        dio->Init();
        // drive = new Drive(motor[0], motor[1]);
    }
    void TestInit() override{
        M5.Lcd.fillScreen(M5.Lcd.color565(0x42, 0x6a, 0xb3));
        M5.Lcd.setTextSize(3);
    }
    void TestPeriodic() override{
        int a = ain->analogRead(0);
        M5.Lcd.setCursor(0, 0);
        Serial.println(a);

        delay(25);
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
    void RobotPeriodic() override{
        // Serial.println("Edited RobotPeriodic()");
    }
};
RobotSystem* robot;
System* _system;

void setup() {
    robot = new Robot(urc::dio, urc::pwm, urc::ain, urc::motor);
    _system = new System(urc::espNow, urc::dio, 
                            urc::pwm, urc::ain, urc::motor, robot);
    _system->SystemInit();
}


void loop() {
    // Serial.print("Mode ");
    // Serial.println(urc::myData.mode);
    _system->SystemPeriodic();
}
