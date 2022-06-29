#include "System.h"
#include <M5StickCPlus.h>

EspNow* urc::espNow = new EspNow();
MCP23017* urc::dio = NULL;
MCP23017* urc::dio_internal = NULL;
PCA9685* urc::pwm = NULL;
AnalogIn* urc::ain = NULL;
Send_struct urc::myData = {0};
Motor* urc::motor[6] = {NULL};

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
    memcpy(&urc::myData, incomingData, sizeof(urc::myData));
}

System::System(EspNow* _espNow, MCP23017* _dio, MCP23017* _dio_internal, PCA9685* _pwm, AnalogIn* _ain, Motor* _motor[], RobotSystem* _robot){
    system_espNow = _espNow;
    system_dio = _dio;
    system_dio_internal = _dio_internal;
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
    Serial.println("Wire begin");
    system_espNow = new EspNow;
    system_espNow->Init<esp_now_recv_cb_t>(RECEIVER, espNow_func::OnDataRecv);
    Serial.println("EspInit");
    // robot = new RobotSystem(system_dio, system_pwm, system_ain, system_motor);
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