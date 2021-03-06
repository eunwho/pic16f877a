/////////////////////////////////////////////////////////////////////////
//
//	Project Name 	: Input for EW Inverter  
//	Fiele Name	 	: sci.c
///////////////////////////////////////////////////////////////////////////
//
// 8Mhz  baud:38400
//
#include    "./include/header.h"
#include    "./include/extern.h"

void SerialPortSetup(void)
{
	TXSTA=0;
	RCSTA=0;	
	// port \BC\B3\C1\A4 port_C.7=RX --> input, port_C.6=TX --> output
	TRISC=0b10010000;	// debug

	SPBRG = 12;//SPBRG=12;			// 38400
	// SPBRG = 4; // 115200
	
	TXSTA=0b00000100;		// TX : disable,8bit data, Asynchronous mode, 16x mode
	// serial_port_enable();
	RCSTA=0b10011000;//RCSTA=0b10010000;		// RX : disable, clear error
	TXSTAbits.TXEN = 1;     // transmit_enable();    
/*    
	SPBRG = 12;//SPBRG=12;			// 38400
    // RCSTAbits.SPEN = 
    
    PIE1bits.TXIE = 0;

    TXSTA=0;
	RCSTA=0;	
	
	TRISC=0b10010000;	// debug

	TXSTA=0b00000100;		// TX : disable,8bit data, Asynchronous mode, 16x mode
	RCSTA=0b10011000;       //RCSTA=0b10010000;		// RX : disable, clear error
*/
}

void SendChar(char xmit_data)
{
	unsigned long msec_count=0;
	unsigned long start_count;

	start_count = gulRtsCount; 
 	while (!(TXSTAbits.TRMT) && (msec_count < 2 )){ 		// wait untill transmit buffer is empty
		 msec_count = ulGetDelaymSec( start_count);
	 }

	TXREG=xmit_data;		// send character

	start_count = gulRtsCount; 
	msec_count= 0;

 	while (!(TXSTAbits.TRMT) && (msec_count < 2 )){ 		// wait untill transmit buffer is empty
		 msec_count = ulGetDelaymSec( start_count);
	 }
}

void SendSciString(char *string)
{
	int count=0;
	while ((*string) && (count < 20)) {
		SendChar(*(string++));
		count++;
	}
}
//--- end of sci.c
        