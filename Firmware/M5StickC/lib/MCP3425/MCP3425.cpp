#include "MCP3425.h"

MCP3425::MCP3425(uint8_t dAddress) {
    deviceAddress = dAddress;
}

void MCP3425::Init(bool convertMode, int bitMode, int pgaMode) {
    int setting = (convertMode << 4) + (bitMode << 2) + pgaMode + (0b100 << 5);
    Wire.beginTransmission(deviceAddress);
    Wire.write(setting);
    Wire.endTransmission();
}

int MCP3425::analogRead() {
    Wire.requestFrom(deviceAddress, 2);
    double val = ( (Wire.read() << 8 ) + Wire.read() );
    return val;
}