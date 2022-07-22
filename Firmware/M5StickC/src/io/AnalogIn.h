#pragma once

#include <M5StickCPlus.h>
#include <MCP23017.h>
#include <MCP3425.h>

class AnalogIn{
private:
    uint8_t deviceAddress;
    int doutPins[3] = {13, 14, 15};
    MCP23017* channel;
    MCP3425* adc;
public:
    AnalogIn(uint8_t dAddress, MCP23017* dOut, int dOutPins[]);
    void Init(bool convertMode=1, int bitMode=2, int pgaMode=0);
    int analogRead(int pin);
};
