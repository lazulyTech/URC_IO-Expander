#include "RobotSystem.h"

bool test = true;

// Write the codes to run when the robot boots
void RobotSystem::RobotInit(){
    Serial.println("RobotInit()");
    dio->pinMode( 0, OUTPUT);
    dio->pinMode( 1, OUTPUT);
    dio->pinMode( 2, OUTPUT);
    dio->pinMode( 3, OUTPUT);
    dio->pinMode( 4, OUTPUT);
    dio->pinMode( 5, OUTPUT);
    dio->pinMode( 6, OUTPUT);
    dio->pinMode( 7, OUTPUT);
    dio->pinMode( 8, OUTPUT);
    dio->pinMode( 9, OUTPUT);
    dio->pinMode(10, OUTPUT);
    dio->pinMode(11, OUTPUT);
    dio->pinMode(12, OUTPUT);
    dio->pinMode(13, OUTPUT);
    dio->pinMode(14, OUTPUT);
    dio->pinMode(15, OUTPUT);

    dio->Init();
}
void RobotSystem::RobotPeriodic(){
    Serial.println("RobotPeriodic()");
}


void RobotSystem::TestInit(){
    Serial.println("TestInit()");
}
void RobotSystem::TestPeriodic(){
    Serial.println("TestPeriodic()");
}

/*-----------------------*/
/*    Match Functions    */
/*-----------------------*/

void RobotSystem::DisabledInit(){
    Serial.println("DisabledInit()");
}
void RobotSystem::DisabledPeriodic(){
    Serial.println("DisabledPeriodic()");
}

void RobotSystem::AutonomousInit(){
    Serial.println("DisabledInit()");
}
void RobotSystem::AutonomousPeriodic(){
    Serial.println("AutonomousPeriodic()");
}

void RobotSystem::TeleopInit(){
    Serial.println("TeleopInit()");
}
void RobotSystem::TeleopPeriodic(){
    Serial.println("TeleopPeriodic()");
}
