#include <PID_v1.h>
double setpoint = 178; //It will be changed depending on our model
double input, output;
double Kp = 50; //Intial Kp
double Kd = 1.1; //Intial Kd
double Ki = 70; //Intial Ki
PID pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT); //define object of the PID controller
void Setup_PID(int mode,int sample_time,double min_limit,double max_limit){
      //setup PID
    pid.SetMode(mode);
    pid.SetSampleTime(sample_time);
    pid.SetOutputLimits(min_limit, max_limit); //negative means reverse motion and positive means forward motion
}
void Compute(){
  pid.Compute();
}
