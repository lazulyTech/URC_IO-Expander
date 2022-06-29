#pragma once

#include <M5StickCPlus.h>
#include <EspNow.h>
#include <PS4Controller.h>
#include <MCP23017.h>
#include <MCP3425.h>
#include <PCA9685.h>
#include "io/AnalogIn.h"
#include "io/Motor.h"
#include "RobotSystem/RobotSystem.h"

#define MCP_ADDRESS 0x20
#define MCP_INTERNAL_ADDR 0x21
#define PCA_ADDRESS 0x40
#define ADC_ADDRESS 0x68

typedef struct send_struct {
  int mode;
} Send_struct;

typedef struct state {
    bool wasAuto;
    bool wasTeleop;
    bool wasDisable;
    bool wasTest;
} State;

namespace urc{
    extern bool test;

    extern EspNow* espNow;
    extern MCP23017* dio;
    extern MCP23017* dio_internal;
    extern PCA9685* pwm;
    extern AnalogIn* ain;
    extern Send_struct myData;
    extern Motor* motor[6];
}

namespace espNow_func{
    extern void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
    extern void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
}

class System{
private:
    // Send_struct myData = {0};
    State state = {false};

    EspNow* system_espNow;
    MCP23017* system_dio;
    MCP23017* system_dio_internal;
    PCA9685* system_pwm;
    AnalogIn* system_ain;

    RobotSystem* robot;

    Motor* system_motor[6];

public:
    System(EspNow*, MCP23017*, MCP23017*, PCA9685*, AnalogIn*, Motor*[], RobotSystem*);
    void SystemInit();
    void SystemPeriodic();
};