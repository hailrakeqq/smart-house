#include <Arduino.h>
#include "servoMotor.h"
servoMotor::servoMotor(int pin)
{
    servo.attach(pin);
}

String servoMotor::getServoStatus()
{
    int servoPosition = servo.read();
    if(servoPosition == 0)
        return "Servo is close";

    return "Servo is open";
}

void servoMotor::reset(){
    this->servo.write(0);
}

void servoMotor::closeServo()
{
    this->servo.write(0);
}

void servoMotor::openServo()
{
    this->servo.write(90);
}
