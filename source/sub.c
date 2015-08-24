/////////////////////////////////////////////////////////////////////////
//
//	Project Name 	: EWDO-21 Digital Input for EW Inverter
//						  for 크렌코 태양열 발전기
//	Fiele Name	 	: sub.c
//
//  Start 			: 2007.03.25 sunday
//  Finish			: ?			: 
//
///////////////////////////////////////////////////////////////////////////
#SEPARATE
void Nop()
{
	#asm
		nop
	#endasm
}
		
#SEPARATE
char WriteEeprom(char addr,char data)
{

	EEADR 	= addr;
	EEDATA 	= data;

	bit_clear(EECON1,7);				// 	EEPGD(EECON1<7>) == 0 data eeprom access
	bit_set(EECON1,2);					// WREN(EECON1 <2>)

//	global_interrupt_disable();

	EECON2 = 0x55;
	EECON2 = 0xAA;

	bit_set(EECON1,1);					// WR(EECON1<1>)
	bit_clear(EECON1,2);					// WREN(EECON1 <2>)

	delay_ms(10);

//	global_interrupt_enable();

	if( (EECON1 && 0b00000010) != 0) return FALSE;
	else							 return TRUE;
}

#SEPARATE
char ReadEeprom(char addr )
{
	char Temp;

	EEADR = addr;
	bit_clear(EECON1,7);
	bit_set(EECON1,0);

	Temp = EEDATA;
	return	Temp;
}

#SEPARATE
unsigned long ulGetNowCount_msec()
{
	return gulRtsCount;
}

#SEPARATE
unsigned long ulGetDelaymSec(unsigned long Start)
{
	if( gulRtsCount < Start) return 65535 - Start + gulRtsCount;
	else 				   return gulRtsCount - Start;
}	

void delay_msec( unsigned long delay_time)
{
	unsigned long start_count;

	start_count = ulGetNowCount_msec();
	while( ulGetDelaymSec(start_count) < delay_time);
}	

//========================================
// 
// GetErrText  MFxx  xx는 FAULT 번호  
// 
//========================================

#SEPARATE
void ErrorProc(int ErrorCode)
{
}
