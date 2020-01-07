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

//	PORTD bits 4-7 are connected to the LCD data bits 4-7 (high nibble)
//	PORTE bit 0 is connected to the LCD RS input (register select)
//	PORTE bit 1 is connected to the LCD EN bit (enable)

// 4bit setting PORT D data 

#define LCD_STROBE ((LCD_CE = 1),(LCD_CE =0))

void lcd_write(unsigned char c)
{
    PORTD = c & 0xf0;
    LCD_STROBE;
    PORTD = ((c << 4 ) & 0xf0) ;
    LCD_STROBE;
    __delay_us(40);
}
//--- Clear and home the LCD
void lcd_clear(void)
{
    LCD_RS = 0;
    lcd_write(0x01);
    __delay_ms(2);
}
void lcdCursorOff(){
    LCD_RS = 0;
    lcd_write(CURSOR_OFF);
    __delay_ms(2);    
}

void lcd_putch(char c){
    LCD_RS = 1;	// write characters
    PORTD =  c & 0xf0 ; 
    LCD_STROBE;
    PORTD = ((c << 4) & 0xf0);
    LCD_STROBE;
    __delay_us(40);
}

/* write a string of chars to the LCD */

void lcd_puts(const char * s)
{
    int count = 0;
    LCD_RS = 1;	// write characters
    while( (* s) && (count < 20) ){
        lcd_write(* s ++);
        count ++;
    }
}

void lcdCursor(int row,int offset, unsigned char CursorCmd)
{
	int	Addr;
	switch (row)
	{
		case	0	:	Addr=ROW1;	break;
		case	1	:	Addr=ROW2;	break;
		case	2	:	Addr=ROW3;	break;
		case	3	:	Addr=ROW4;	break;
	}
    LCD_RS = 0;
    lcd_write(Addr+offset+DDRAM);
	lcd_write(CursorCmd);
}

/* write one character to the LCD */


// Go to the specified position

void lcd_goto(unsigned char pos){
    LCD_RS = 0;
    lcd_write(0x80+pos);
}

/* initialise the LCD - put into 4 bit mode */
void DisplayChar(int row, int offset, char c)
{
    int	Addr;
	switch (row)
	{
		case	0	:	Addr=ROW1;	break;
		case	1	:	Addr=ROW2;	break;
		case	2	:	Addr=ROW3;	break;
		case	3	:	Addr=ROW4;	break;
	}
    //lcd_goto(row+offset);
    //lcdCursor(row,offset,DISPLAY_ON );//
    // lcd_goto(Addr+offset);
    lcd_goto(Addr+offset);    
    lcd_putch(c);
}

void lcd_init(void){
    LCD_RW = 0;	// write control bytes
    
    LCD_RS = 0;	// write control bytes
    __delay_ms(15);	// power on delay
    PORTD = 0x30;	// attention!
    LCD_STROBE;
    __delay_ms(5);
    LCD_STROBE;
    __delay_us(100);
    LCD_STROBE;
    __delay_ms(5);
    PORTD = 0x20;	// set 4 bit mode
    LCD_STROBE;
    __delay_us(40);
    lcd_write(0x28);	// 4 bit mode, 1/16 duty, 5x8 font
    lcd_write(0x08);	// display off
    lcd_write(0x0F);	// display on, blink curson on
    lcd_write(0x06);	// entry mode
}

void printLCD(int row, int offset,char * string,int len)
{
    int	i,Addr;
    int length;
    
    if( len > 19 ) length = 19;
    else            length = len;
    
	switch (row)
	{
		case	0	:	Addr=ROW1;	break;
		case	1	:	Addr=ROW2;	break;
		case	2	:	Addr=ROW3;	break;
		case	3	:	Addr=ROW4;	break;
	}
    lcd_goto(Addr+offset);
    i = 0;
    while((*string) && (i < length) ){
        i++;
        lcd_putch(*string ++);
    }
}

// end of file