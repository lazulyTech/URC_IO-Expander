#include "RobotSystem.h"

// Write the codes to run when the robot boots
void RobotSystem::RobotInit(){
    Serial.println("RobotInit()");
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
