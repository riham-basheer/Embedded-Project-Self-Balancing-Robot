#include "LMotorController.h"
int ENA = 5;
int IN1 = 6;
int IN2 = 7;
int IN3 = 8;
int IN4 = 9;
int ENB = 10;
double msf_Left = 0.6; //Motor speed factor for left motor
double msf_Right = 0.5; //Motor speed factor for right motor
LMotorController motorController(ENA, IN1, IN2, ENB, IN3, IN4, msf_Left, msf_Right);
void Move(double output,int min_speed){
  motorController.move(output,min_speed);
}
