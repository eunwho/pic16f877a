/////////////////////////////////////////////////////////////////////////
//
//	Project Name 		: LCD INPUT for Montrol Inverter
//	Fiele Name		 	: LCD.c
// 	Discription			: ICD2를 이용한 프로젝트
//  이전 소스일자 		: 2004.03.31
//  이전 소스일자 		: 2004.03.31
//
// LCD 입력기의 입력 범위를 제한 하는 기능을 삽입하는 방안
///////////////////////////////////////////////////////////////////////////
// why redefine this  in spite of defined in 16F877A.c   

//#use delay(clock=8000000)		// debug
#include    "./include/header.h"
#include    "./include/extern.h"

void Busy()
{
	int	LCD_Busy;

	__delay_us(10);	// debug
	PORTD = 0x00;
	LCD_RW = 1;
	LCD_CE = 1;
    __delay_ms(5);
	LCD_CE = 0 ;
	LCD_RS = 0;
	LCD_RW = 0; 	
}


void LCD_Cmd(unsigned char cmd)
{
	PORTD = cmd;
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_CE = 1;
	__delay_ms(2);						   
	LCD_CE = 0;
	__delay_ms(2);						   
	LCD_CE = 1;
}

// LCD initialization after power on


void LCD_Initialization()
{
	LCD_CE = 0;
	LCD_RS = 0;
	LCD_RW = 0;

	PORTD = 0;
	PORTD = 0x38;

	LCD_CE = 1;
    __delay_us(10);
	LCD_CE = 0;
	__delay_ms(20);
	PORTD = 0x38;
	LCD_CE = 1;
	Nop();
	Nop();
	LCD_CE=0;
	__delay_ms(5);
	LCD_Cmd(DISPLAY_ON);		// display on, curse off, blink off
	LCD_Cmd(0x01);				// display on, curse off, blink off
	LCD_Cmd(0x06);				// LCD clear, curse home
	LCD_Cmd(0x80);				// initial DDRAM address
	LCD_Cmd(0x01);				// LCD clear,curse home
}

void LCD_AddrSet(int addr)
{
	Busy();
	PORTD = (unsigned)(addr+DDRAM);
	LCD_CE = 1;
    Nop();
	LCD_CE = 0;
}

void DisplayChar(int row,int offset,char data)
{
	int	ROW_Addr;
	switch (row)
	{
		case	0	:	ROW_Addr=ROW1;	break;
		case	1	:	ROW_Addr=ROW2;	break;
		case	2	:	ROW_Addr=ROW3;	break;
		case	3	:	ROW_Addr=ROW4;	break;
	}
	LCD_CE = 0;
	LCD_RS = 0;
	LCD_RW = 0;

	LCD_AddrSet(ROW_Addr+offset);
	Busy();
	PORTD = data;
	LCD_RS = 1;
	LCD_CE = 1;
	LCD_CE = 0;
	LCD_RS = 0;
}

void lcdCursor(int row,int offset,char CursorCmd)
{
	int	Addr;
	switch (row)
	{
		case	0	:	Addr=ROW1;	break;
		case	1	:	Addr=ROW2;	break;
		case	2	:	Addr=ROW3;	break;
		case	3	:	Addr=ROW4;	break;
	}
	LCD_AddrSet(Addr+offset);
	LCD_Cmd(CursorCmd);
}

void printLCD(int row, int offset,char * string)
{
	while (* string && ( offset <  20)){
		DisplayChar(row,offset++,*string++);
	}
}

// end of file