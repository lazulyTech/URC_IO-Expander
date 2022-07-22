#pragma once

#include <M5StickCPlus.h>
#include <MCP23017.h>
#include <PCA9685.h>

class Motor {
private:
    // MCP23017* dio_mot;
    PCA9685* pwm_mot;
    int pin[2];
public:
    Motor(PCA9685* pwm_);
    void setPins(int pwmPinA, int pwmPinB);
    void move(int speed);
    void stop();
};

class Drive {
private:
    Motor* motorL;
    Motor* motorR;
public:
    Drive(Motor* motor_l, Motor* motor_r);
    void move(int speedL, int speedR);
    void stop();
};