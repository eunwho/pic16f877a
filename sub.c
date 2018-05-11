//	Project Name 	: EWDO-21 Digital Input for EW Inverter
//	Fiele Name	 	: sub.c

#include    "./include/header.h"
#include    "./include/extern.h"

void Nop()
{
    __delay_us(1);
}

int WriteEeprom(char addr,char data)
{

	EEADR 	= addr;
	EEDATA 	= data;

	EECON1bits.EEPGD = 0;       //bit_clear(EECON1,7);
	EECON1bits.WREN = 1;		// WREN(EECON1 <2>)

//	global_interrupt_disable();

	EECON2 = 0x55;
	EECON2 = 0xAA;

	EECON1bits.WR = 1 ;     // bit_set(EECON1,1);
	EECON1bits.WREN = 0;    //bit_clear(EECON1,2);

	__delay_ms(10);

	if( EECON1bits.WR ) return 0;
	else				 return 1;
}

char ReadEeprom(char addr )
{
	char Temp;

	EEADR = addr;
	EECON1bits.EEPGD = 0;
	EECON1bits.RD = 1;

	Temp = EEDATA;
	return	Temp;
}

unsigned long ulGetNowCount_msec()
{
	return gulRtsCount;
}

unsigned long ulGetDelaymSec(unsigned long Start)
{
	if( gulRtsCount < Start) return 65535 - Start + gulRtsCount;
	else 				   return gulRtsCount - Start;
}	
// end of file