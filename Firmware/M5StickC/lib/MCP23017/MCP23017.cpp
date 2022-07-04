#include "MCP23017.h"

MCP23017::MCP23017(uint8_t dAddress){
    deviceAddress = dAddress;
}

void MCP23017::pinMode(int pin, int status) {
    switch (status) {
    case INPUT:
        status = 1;
        break;
    case OUTPUT:
        status = 0;
        break;
    default:
        break;
    }
    bool channel = 0;
    if(pin >= 8){
        pin -=8;
        channel = 1;
    }
    if((bufferStatus[channel] & (1 << pin)) >> pin == 0 ) {
        bufferStatus[channel] += status << pin;
    }
}

void MCP23017::Init() {
    Wire.beginTransmission(deviceAddress);
    Wire.write(0x00);
    Wire.write(bufferStatus[0]);
    Wire.endTransmission();

    Wire.beginTransmission(deviceAddress);
    Wire.write(0x01);
    Wire.write(bufferStatus[1]);
    Wire.endTransmission();
}

void MCP23017::digitalWrite(int pin, int status){
    bool channel = 0;
    if(pin >= 8){
        pin -=8;
        channel = 1;
    }
    bufferOut[channel][pin] = (bool)status;
    uint8_t write = 0;
    for (int i = 0; i < 8; i++){
        write += bufferOut[channel][i] * pow(2, i);
    }
    
    Wire.beginTransmission(deviceAddress);
    Wire.write(0x12 + channel);
    Wire.write(write);
    Wire.endTransmission();
}

uint8_t MCP23017::digitalRead(int pin) {
    bool channel = 0;
    if(pin >= 8){
        pin -=8;
        channel = 1;
    }

    Wire.beginTransmission(deviceAddress);
    Wire.write(0x12 + channel);
    Wire.endTransmission();
    Wire.requestFrom(deviceAddress, (uint8_t)1);
    uint8_t allData = Wire.read();
    Wire.endTransmission();

    uint8_t data = allData & (1 << pin);
    data = data >> pin;
  
    return data;
}

void MCP23017::getStatus(int channel, bool* array){
    for(int i = 0; i < sizeof(bufferOut[channel]); i++){
        *(array + i) = bufferOut[channel][i];
    }
}