//Including Files
#include "MPU.h"
#include "Motor.h"
#include "PID.h"

#define MIN_ABS_SPEED 20

volatile bool mpuInterrupt = false;
void dmpDataReady() //this function is called when the buffer is full to generate interrupt
{
    mpuInterrupt = true;
}

void setup()
{
    // join I2C bus
    Join_I2C();
    
    // initialize device
    Intialize_MPU();    
    // load and configure the DMP
    devStatus = Intialize_DMP();

    // Add offset for error correction and calibration
    Set_MPU_Offset(220,76,-85,1688);
    
    Enable_DMP();
    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = Get_MPU_IntStatus();
    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    dmpReady = true;

    // get expected DMP packet size for comparison
    packetSize = Get_DMP_Packet_Size();
    
    //setup PID
    Setup_PID(AUTOMATIC,10,-255,255);  
}


void loop()
{
    // if programming failed, don't try to do anything
    if (!dmpReady) return;
    fifoCount = Get_MPU_FIFO_Count();
    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize)
    {
        //no mpu data - performing PID calculations and output to motors
        Compute();
        Move(output,MIN_ABS_SPEED);
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = Get_MPU_IntStatus();
    // get current FIFO count
    fifoCount = Get_MPU_FIFO_Count();
    if (mpuIntStatus & 0x02)
    {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = Get_MPU_FIFO_Count();

        // read a packet from FIFO
        Read_MPU_Packet(fifoBuffer,packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

        Get_MPU_Statistics(q,fifoBuffer,gravity,EulerAngles);
        input = EulerAngles[1] * 180/M_PI + 180;
   }
}
