#pragma once

#include <M5StickCPlus.h>

class MCP3425{
private:
    uint8_t deviceAddress;

public:
    MCP3425(uint8_t dAddress);
    void Init(bool convertMode=1, int bitMode=2, int pgaMode=0);
    /*--------------------------*/
    /*  convertMode             */
    /*      false: one shot     */
    /*    * true : consecutive  */
    /*  bitMode                 */
    /*         0 : 12 bit       */
    /*         1 : 14 bit       */
    /*    *    2 : 16 bit       */
    /*  pgaMode                 */
    /*    * 0 : x1              */
    /*      1 : x2              */
    /*      2 : x4              */
    /*      3 : x8              */
    /*--------------------------*/
    // 0b10011000
    
    int analogRead();
};
