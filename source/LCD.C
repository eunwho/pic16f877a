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

#SEPARATE
void Busy()
{
	int	LCD_Busy;

	delay_us(10);	// debug
	do
	{
		output_d(0);
		output_high(LCD_RW);
		output_high(LCD_CE);
		LCD_Busy = (input_d()) & 0x80;	  	// busy flag mask : bit7
		output_low(LCD_CE);
	} while (LCD_Busy);
	delay_ms(2);   // debug
	output_low(LCD_CE);
	output_low(LCD_RS);
	output_low(LCD_RW); 	
}

#SEPARATE
void LCD_Cmd(int cmd)
{
	output_d(cmd);
	output_low(LCD_RS);
	output_low(LCD_RW);
	output_high(LCD_CE);
	delay_ms(2);						   
	output_low(LCD_CE);
	delay_ms(2);						   
	output_high(LCD_CE);
}

// LCD initialization after power on

#SEPARATE
void LCD_Initialization()
{
	output_low(LCD_CE);
	output_low(LCD_RS);
	output_low(LCD_RW);

	output_d(0);
	output_d(0x38);

	output_high(LCD_CE);
	Nop();
	Nop();
	output_low(LCD_CE);

	delay_ms(20);

	output_d(0x38);

	output_high(LCD_CE);
	Nop();
	Nop();
	output_low(LCD_CE);

	delay_ms(5);

	LCD_Cmd(DISPLAY_ON);		// display on, curse off, blink off
	LCD_Cmd(0x01);				// display on, curse off, blink off
	LCD_Cmd(0x06);				// LCD clear, curse home
	LCD_Cmd(0x80);				// initial DDRAM address
	LCD_Cmd(0x01);				// LCD clear,curse home
}

// LCD의 어드레스 설정
#SEPARATE
void LCD_AddrSet(int addr)
{
	Busy();
	output_d(addr+DDRAM);
	output_high(LCD_CE);
	output_low(LCD_CE);
}

// LCD에 문자 출력
#SEPARATE
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
	output_low(LCD_CE);
	output_low(LCD_RS);
	output_low(LCD_RW);

	LCD_AddrSet(ROW_Addr+offset);
	Busy();
	output_d(data);
	output_high(LCD_RS);
	output_high(LCD_CE);
	output_low(LCD_CE);
	output_low(LCD_RS);
}

#SEPARATE
void Cursor(int row,int offset,unsigned CursorCmd)
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

#SEPARATE
void PrintLCD(int row,int offset,char *string)
{
	while (*string && ( offset <  20)){
		DisplayChar(row,offset++,*string++);
	}
}

