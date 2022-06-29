#pragma once

#include <M5StickCPlus.h>
#include <MCP23017.h>
#include <MCP3425.h>
#include <PCA9685.h>
#include "io/AnalogIn.h"
#include "io/Motor.h"

class RobotSystem{
public:
    MCP23017* dio;
    PCA9685* pwm;
    AnalogIn* ain;
    Drive* drive;
    Motor* motor[6];
public:
    RobotSystem(MCP23017* _dio, PCA9685* _pwm, AnalogIn* _ain, Motor* _motor[]){
        dio = _dio;
        pwm = _pwm;
        ain = _ain;
        for(int i=0; i<6; i++){
            motor[i] = _motor[i];
        }
    }
    virtual void RobotInit();
    virtual void RobotPeriodic();

    virtual void DisabledInit();
    virtual void DisabledPeriodic();
    
    virtual void AutonomousInit();
    virtual void AutonomousPeriodic();
    
    virtual void TeleopInit();
    virtual void TeleopPeriodic();

    virtual void TestInit();
    virtual void TestPeriodic();
};
