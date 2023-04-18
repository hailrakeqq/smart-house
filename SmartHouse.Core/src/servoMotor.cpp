#include "include.h"
#include <Servo.h>

servoMotor::servoMotor(int pin)
{
    servo.attach(pin);
}

servoMotor::getServoStatus()
{
    int servoPosition = servo.read();
    if(servoPosition == 0)
        return "Servo is close";

    return "Servo is open";
}

servoMotor::reset(){
    servo.write(0);
}

servoMotor::closeServo()
{
    servo.write(0);
}

servoMotor::openServo()
{
    servo.write(90);
}

servoMotor::~servoMotor()
{
    servo.detach();
}