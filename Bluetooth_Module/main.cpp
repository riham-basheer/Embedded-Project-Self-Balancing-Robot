#include "BT_Connect.h"
#include "LMotorDrive.h"

// Constants :

/* Pins */
const int ENA_Pin = 3;             // number of enable pin of motor A
const int INPUT1_Pin = 4;          // number of IN1 pin
const int INPUT2_Pin = 5;          // number of IN2 pin

const int ENB_Pin = 6;             // number of enable pin of motor B
const int INPUT3_Pin = 7;          // number of IN3 pin
const int INPUT4_Pin = 8;          // number of IN4 pin

const double msf_Left = 0.6;       // Motor speed factor for left motor
const double msf_Right = 0.5;      // Motor speed factor for right motor
const int MIN_ABS_SPEED = 20; 

LMotorDrive motorDrive = LMotorDrive(ENA_Pin, INPUT1_Pin, INPUT2_Pin, ENB_Pin, INPUT3_Pin, INPUT4_Pin, msf_Left, msf_Right);

// Variables :
volatile uint8_t USART_ReceiveBuffer; // Global Buffer
int bitVal;

// RX Complete interrupt service routine
ISR(USART_RX_vect)
{
	USART_ReceiveBuffer = UDR0;
  String str = (char*)&USART_ReceiveBuffer;
  bitVal = (str.toInt());
	
  switch (bitVal) 
  {
    case 1:                      
    motorDrive.move(msf_Left, msf_Right, MIN_ABS_SPEED);
    break;

    case 2:                
    motorDrive.move(-msf_Left, -msf_Right, MIN_ABS_SPEED);
    break;

    case 3:         
    motorDrive.turnLeft(MIN_ABS_SPEED, true);
    break;
        
    case 4:                     
    motorDrive.turnRight(MIN_ABS_SPEED, true);
    break;
        
    case 5:                                            
    motorDrive.stopMoving();
    break;      
  }
}

int main()
{  
  initialize_USART();
  // Enable receive complete interrupt
	UCSR0B |= RX_COMPLETE_INTERRUPT;
	while (1)
	{
    // sleep mode or (other balancing calc.)
	}
	return 0;
}