#pragma once

#include <M5StickCPlus.h>

class PCA9685 {
private:
    uint8_t deviceAddress;
    int PWMmax = 480;
    int PWMmin = 110;
    float pwmFreq = 50;
    void setPWM(uint8_t num, uint16_t on, uint16_t off);
public:
    PCA9685(uint8_t dAddress);
    void Init();
    void setPWMFreq(float freq=50);
    void setServoRange(int min=150, int max=600);
    void moveServo(int pin, int ang);
    void analogWrite(int pin, int duty);
};

