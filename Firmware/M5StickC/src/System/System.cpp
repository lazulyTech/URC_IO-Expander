#include "System.h"
#include <M5StickCPlus.h>

EspNow* urc::espNow = new EspNow();
MCP23017* urc::dio = new MCP23017(MCP_ADDRESS);
// MCP23017* urc::dio_internal = new MCP23017(MCP_INTERNAL_ADDR);
PCA9685* urc::pwm = new PCA9685(PCA_ADDRESS);
int pinToAnalog[3] = {12,13,14};
AnalogIn* urc::ain = new AnalogIn(ADC_ADDRESS, urc::dio, pinToAnalog);
Send_struct urc::myData = {0, 0};
Motor* urc::motor[6] = {(new Motor(urc::pwm)),
                        (new Motor(urc::pwm)),
                        (new Motor(urc::pwm)),
                        (new Motor(urc::pwm)),
                        (new Motor(urc::pwm)),
                        (new Motor(urc::pwm))};

void espNow_func::OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    char macStr[18];
    Serial.print("Packet to: ");
    // Copies the sender mac address to a string
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.print(macStr);
    Serial.print(" send status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
void espNow_func::OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    Send_struct buf;
    memcpy(&buf, incomingData, sizeof(buf));
    if(buf.id == 0 || buf.id == urc::teamNumber) urc::myData = buf;
}

System::System(EspNow* _espNow, MCP23017* _dio, PCA9685* _pwm, AnalogIn* _ain, Motor* _motor[], RobotSystem* _robot){
    system_espNow = _espNow;
    system_dio = _dio;
    // system_dio_internal = _dio_internal;
    system_pwm = _pwm;
    system_ain = _ain;
    for(int i=0; i<6; i++){
        system_motor[i] = *(_motor + i);
    }
    robot = _robot;
}
void System::SystemInit(){
    M5.begin();
    M5.Lcd.fillScreen(WHITE);
    Wire.begin(32,33);

    system_espNow = new EspNow;
    system_espNow->Init<esp_now_recv_cb_t>(RECEIVER, espNow_func::OnDataRecv);

    for(int i = 13; i < 16; i++){
        system_dio->pinMode(i, OUTPUT);
    }
    // system_dio_internal->Init();
    // Serial.println("dio_internal Init");

    system_pwm->Init();
    system_pwm->setPWMFreq(1000);
    // Serial.println("pwm Init");

    system_ain->Init();
    // Serial.println("ain Init");
    
    for (int i = 0; i < 6; i++){
        system_motor[i]->setPins(2*i +4, 2*i +5);
        // Serial.print("motor ");
        // Serial.print(i);
        // Serial.println(" Init");
    }
    robot->RobotInit();
    if(urc::test){
        robot->TestInit();
    }
}
void System::SystemPeriodic(){
    M5.update();
    if(urc::test) robot->TestPeriodic();
    else {
        switch(urc::myData.mode){
            case 0:
                if(!state.wasDisable){
                    robot->DisabledInit();
                    state.wasDisable = true;
                }
                robot->DisabledPeriodic();
                state.wasAuto = false;
                state.wasTeleop = false;
                break;
            case 1:
                if(!state.wasAuto){
                    robot->AutonomousInit();
                    state.wasAuto = true;
                }
                robot->AutonomousPeriodic();
                state.wasDisable = false;
                state.wasTeleop = false;
                break;
            case 2:
                if(!state.wasTeleop){
                    robot->TeleopInit();
                    state.wasTeleop = true;
                }
                robot->TeleopPeriodic();
                state.wasDisable = false;
                state.wasAuto = false;
                break;
            default:
                break;
        }
    }
    robot->RobotPeriodic();
}
