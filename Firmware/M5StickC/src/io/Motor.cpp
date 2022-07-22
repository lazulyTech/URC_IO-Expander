#include "Motor.h"

Motor::Motor(PCA9685* pwm_){
    // dio_mot = dio_;
    pwm_mot = pwm_;
}
void Motor::setPins(int pwmPinA, int pwmPinB){
    // pin[0] = dinA;
    // pin[1] = dinB;
    pin[0] = pwmPinA;
    pin[1] = pwmPinB;
}
void Motor::move(int speed){
    if(speed > 0){
        if(speed >= 4096) speed = 4095;
        // dio_mot->digitalWrite(pin[0], HIGH);
        // dio_mot->digitalWrite(pin[1], LOW);
        pwm_mot->analogWrite(pin[0], speed);
        pwm_mot->analogWrite(pin[1], 0);
    } 
    else if(speed < 0){
        if(speed <= -4096) speed = -4095;
        // dio_mot->digitalWrite(pin[0], LOW);
        // dio_mot->digitalWrite(pin[1], HIGH);
        pwm_mot->analogWrite(pin[0], 0);
        pwm_mot->analogWrite(pin[1], -speed);
    }
    else {
        // dio_mot->digitalWrite(pin[0], HIGH);
        // dio_mot->digitalWrite(pin[1], HIGH);
        pwm_mot->analogWrite(pin[0], 0);
        pwm_mot->analogWrite(pin[1], 0);
    }
}
void Motor::stop(){
    // dio_mot->digitalWrite(pin[0], LOW);
    // dio_mot->digitalWrite(pin[1], LOW);
    pwm_mot->analogWrite(pin[0], 4095);
    pwm_mot->analogWrite(pin[2], 4095);
}

Drive::Drive(Motor* motor_l, Motor* motor_r){
    motorL = motor_l;
    motorR = motor_r;
}
void Drive::move(int speedL, int speedR){
    motorL->move(speedL);
    motorR->move(speedR);
}
void Drive::stop(){
    motorL->stop();
    motorR->stop();
}
