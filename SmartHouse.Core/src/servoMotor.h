#include "include.h"

class servoMotor{
    private:
        Servo servo;

    public:
        servoMotor(int pin);
        String getServoStatus();
        void reset();
        void openServo();
        void closeServo();
};