#include "AnalogIn.h"

AnalogIn::AnalogIn(uint8_t dAddress, MCP23017* dOut, int dOutPins[]){
    deviceAddress = dAddress;
    channel = dOut;
    adc = new MCP3425(deviceAddress);
    for (int i = 0; i < 3; i++){
        doutPins[i] = dOutPins[i];
    }
    
}

void AnalogIn::Init(bool convertMode, int bitMode, int pgaMode){
    adc->Init(convertMode, bitMode, pgaMode);
    for(int i=0; i < 3; i++){
        channel->pinMode(doutPins[i], OUTPUT);
    }
}

int AnalogIn::analogRead(int pin){
    if((pin && 0b001) >> 0){
        channel->digitalWrite(doutPins[0], HIGH);
    } else {
        channel->digitalWrite(doutPins[0], LOW);
    }
    if((pin && 0b010) >> 1){
        channel->digitalWrite(doutPins[1], HIGH);
    } else {
        channel->digitalWrite(doutPins[1], LOW);
    }
    if((pin && 0b100) >> 2){
        channel->digitalWrite(doutPins[2], HIGH);
    } else {
        channel->digitalWrite(doutPins[2], LOW);
    }
    return adc->analogRead();
}