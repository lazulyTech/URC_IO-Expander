#include "PCA9685.h"

PCA9685::PCA9685(uint8_t dAddress){
    deviceAddress = dAddress;
}

void PCA9685::Init(){
    Wire.beginTransmission(deviceAddress);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.endTransmission();
}

void PCA9685::setPWM(uint8_t num, uint16_t on, uint16_t off) {
  //Serial.print("Setting PWM "); Serial.print(num); Serial.print(": "); Serial.print(on); Serial.print("->"); Serial.println(off);

  Wire.beginTransmission(deviceAddress);
  Wire.write(0x06 + 4 * num);
  Wire.write(on);
  Wire.write(on>>8);
  Wire.write(off);
  Wire.write(off>>8);
  Wire.endTransmission();
}

void PCA9685::setPWMFreq(float freq){
    pwmFreq = freq;
    float prescaleval = 25000000;
    prescaleval /= 4096;
    prescaleval /= freq;
    prescaleval -= 1;
    uint8_t prescale = floor(prescaleval + 0.5);
    
    Wire.beginTransmission(deviceAddress);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(deviceAddress, (uint8_t)1);
    uint8_t oldreg = Wire.read();
    uint8_t newreg = (oldreg&0x7F) | 0x10; // sleep
    Wire.beginTransmission(deviceAddress); // go to sleep
    Wire.write(0x00);
    Wire.write(newreg);
    Wire.endTransmission();

    Wire.beginTransmission(deviceAddress); // set the prescaler
    Wire.write(0xfe);
    Wire.write(prescale);
    Wire.endTransmission();
    
    Wire.beginTransmission(deviceAddress);
    Wire.write(0x00);
    Wire.write(oldreg);
    Wire.endTransmission();
    delay(5);

    Wire.beginTransmission(deviceAddress); //  This sets the MODE1 register to turn on auto increment.
    Wire.write(0x00);
    Wire.write(oldreg | 0xa1);
    Wire.endTransmission();
}

void PCA9685::setServoRange(int min, int max){
    PWMmin = min;
    PWMmax = max;
}

void PCA9685::moveServo(int pin, int ang){
    if (ang <= 0) ang = 0;
    if (ang >= 180) ang = 180;
    ang = map(ang, 0, 180, PWMmin, PWMmax);
    setPWM(pin, 0, ang);
}

void PCA9685::analogWrite(int pin, int duty){
    setPWM(pin, 0, duty);
}
