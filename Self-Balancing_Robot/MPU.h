#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
//Define variables for MPU control
bool dmpReady = false;  // set true if Digital Motion Processor init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO -- see datasheet p.43
uint8_t fifoBuffer[64]; // FIFO storage buffer -- see datasheet p.44

// Define variables needed by the functions in the libirary 
Quaternion q;           // [w, x, y, z]
VectorFloat gravity;    // [x, y, z]            
float EulerAngles[3];   // [yaw, pitch, roll] 

MPU6050 mpu; //define object of type MPU


void Intialize_MPU(){
  mpu.initialize();
}

uint8_t Get_MPU_IntStatus(){
return mpu.getIntStatus();
}

uint8_t Intialize_DMP(){
  return mpu.dmpInitialize();
}
void Enable_DMP(){
  mpu.setDMPEnabled(true);
}

uint8_t Get_DMP_Packet_Size(){
  return mpu.dmpGetFIFOPacketSize();
}
void Join_I2C(){
// join I2C bus
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
      TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif
}
void Set_MPU_Offset(double GyroX,double GyroY,double GyroZ,double AccZ){
    // Add offset for error correction and calibration
    mpu.setXGyroOffset(GyroX);
    mpu.setYGyroOffset(GyroY);
    mpu.setZGyroOffset(GyroZ);
    mpu.setZAccelOffset(AccZ); // 1688 factory default for our chip
}
uint8_t Get_MPU_FIFO_Count(){
  mpu.getFIFOCount();
}

void Read_MPU_Packet(uint8_t fifoBuffer,uint16_t packetSize){
  mpu.getFIFOBytes(fifoBuffer, packetSize);
}
void Get_MPU_Statistics(Quaternion q,uint8_t fifoBuffer,VectorFloat gravity,float * EulerAngles){
  mpu.dmpGetQuaternion(&q, fifoBuffer);
  mpu.dmpGetGravity(&gravity, &q);
  mpu.dmpGetYawPitchRoll(EulerAngles, &q, &gravity);
}
