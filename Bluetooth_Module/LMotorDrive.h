#ifndef LMotorDrive_h
#define LMotorDrive_h

#include "Arduino.h"


class LMotorDrive
{
protected:
    int _ena, _in1, _in2, _enb, _in3, _in4;
    int _currentSpeed;
    double _motorAConst, _motorBConst;
    
public:
    LMotorDrive(int enA, int in1, int in2, int enB, int in3, int in4, double motorAConst, double motorBConst);
    void move(int leftSpeed, int rightSpeed, int minAbsSpeed);
    void move(int speed);
    void move(int speed, int minAbsSpeed);
    void turnLeft(int speed, bool kick);
    void turnRight(int speed, bool kick);
    void stopMoving();
};

#endif