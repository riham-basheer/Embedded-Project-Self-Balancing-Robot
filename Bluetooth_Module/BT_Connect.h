#ifndef BT_CONNECT_h
#define BT_CONNECT_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define F_CPU 16000000UL          // CPU Frequency
#define USART_BAUDRATE 9600       // Baud Rate
#define BAUD_PRESCALER (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define ASYNCHRONOUS (0<<UMSEL00) // USART Mode Selection : Asynchronus

#define ONE_BIT (0<<USBS0)
#define TWO_BIT (1<<USBS0)
#define STOP_BIT ONE_BIT          // USART Stop Bit Selection

#define DISABLED    (0<<UPM00)
#define EVEN_PARITY (2<<UPM00)
#define ODD_PARITY  (3<<UPM00)
#define PARITY_MODE  DISABLED    // USART Parity Bit Selection

#define FIVE_BIT  (0<<UCSZ00)
#define SIX_BIT   (1<<UCSZ00)
#define SEVEN_BIT (2<<UCSZ00)
#define EIGHT_BIT (3<<UCSZ00)
#define NINE_BIT  (7<UCSZ00)
#define NO_OF_DATA_BITS   EIGHT_BIT     // USART Data Bit Selection

#define RX_COMPLETE_INTERRUPT (1<<RXCIE0) // Enable USART receive complete interrupt

void initialize_USART();

#endif