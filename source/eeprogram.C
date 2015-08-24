/////////////////////////////////////////////////////////////////////////
//
//	Project Name 		: LCD INPUT for Montrol Inverter
//	Fiele Name		 	: eeprogram.h
// 	Discription			: ICD2를 이용한 프로젝트
//	최근 변경 날자 		: 2004.12.23
//  이전 소스일자 		: 2004.12.23
//
///////////////////////////////////////////////////////////////////////////


/*

EECON1
	EEPGD bit7
		0	data memory reset -> 0;
		1   program memory
		


EEIF(PIR2)


Reading Data EEPROM Memory

	write	EEADR
	clear 	EEPGD(EECON1<7>)
	set	  	RD(EECON1<0>)
	read	EEDATA
	

Writing Data EEPROM Memory

	write	EEADR
	write	EEDATA

	clear 	EEPGD(EECON1<7>)
	set		WREN(EECON1<2>)
	
	all interrupt off;
	
	write	0x55 to EECON2  // two step process first to w and EECON2
	write	0xAA to EECON2	// two step process first to w and EECON2
	
	set		WR(EECON1<1>)

	clear	WREN(EECON1<2>)
	
	wait for clear WR(EECON1<1>)
*/

