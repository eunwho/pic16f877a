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

void SerialPortSetup()
{
	TXSTA=0;
	RCSTA=0;	
	
	TRISC=0b10010000;	// debug

	SPBRG = 12;//SPBRG=12;			// 38400
	
	TXSTA=0b00000100;		// TX : disable,8bit data, Asynchronous mode, 16x mode
	RCSTA=0b10011000;       //RCSTA=0b10010000;		// RX : disable, clear error
	TXSTAbits.TXEN = 1;     // transmit_enable();
}

int getSciMsg(unsigned char * str)
{
	int count = 0;

	while( sci_rx_msg_start != sci_rx_msg_end && count < 20 )
	{		
		*(str ++) = sci_rx_msg_box[sci_rx_msg_start ++ ];
		if( sci_rx_msg_start >= SCI_RX_MSG_SIZE ) sci_rx_msg_start = 0;		
		count ++;
	}
	*str = 0;
	return count;
}


void SendChar(char xmit_data)
{
	unsigned long msec_count=0;
	unsigned long start_count;

	start_count = ulGetNowCount_msec();
 	while (!(TXSTAbits.TRMT) && (msec_count < 2 )){ 		// wait untill transmit buffer is empty
		 msec_count = ulGetDelaymSec( start_count);
		Nop();
	 }

	TXREG=xmit_data;		// send character

	start_count = ulGetNowCount_msec();
	msec_count= 0;

 	while (!(TXSTAbits.TRMT) && (msec_count < 2 )){ 		// wait untill transmit buffer is empty
		 msec_count = ulGetDelaymSec( start_count);
		Nop();
	 }
}

void SendSciString(char *string)
{
	int count=0;
	while ((*string) && (count < 40)) {
		SendChar(*(string++));
		count++;
	}
}
//--- end of sci.c
        