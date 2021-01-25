#include "BT_Connect.h"

void initialize_USART()
{
	// Set Baud Rate
	UBRR0H = BAUD_PRESCALER >> 8;
	UBRR0L = BAUD_PRESCALER;
	
	// Set Frame Format
	UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | NO_OF_DATA_BITS;
	
	// Enable Receiver
	UCSR0B = (1<<RXEN0);
	
	//Enable Global Interrupts
	sei();
}