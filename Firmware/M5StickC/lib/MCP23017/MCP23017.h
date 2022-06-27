#pragma once

#include <M5StickCPlus.h>

class MCP23017{
private:
    uint8_t deviceAddress;
    uint8_t bufferStatus[2] = {};
    bool bufferOut[2][8] = {};

public:
    MCP23017(uint8_t dAddress);
    void pinMode(int pin, int status);
    void Init();
    void digitalWrite(int pin, int status);
    uint8_t digitalRead(int pin);
    void getStatus(int channel, bool* array);
};
