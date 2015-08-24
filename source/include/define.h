#ifndef		__DEFINE_H_
#define		__DEFINE_H_

#byte	INDF		=	0x00
#byte	TIMER0 		=	0x01
#byte	PCL		=	0x02
#byte	STATUS		=	0x03
#byte	FSR		=	0x04
#byte	PORTA 		= 	0x05
#byte	PORTB 		= 	0x06
#byte	PORTC 		= 	0x07
#byte	PORTD 		= 	0x08
#byte	PORTE 		= 	0x09
#byte	PCLATH		=	0x0A
#byte	INTCON		=	0x0B
#byte	PIR1		=	0x0C
#byte	PIR2		=	0x0D
#byte	TIMER1_L	=	0x0E
#byte	TIMER1_H	=	0x0F
#byte	T1CON		=	0x10
#byte	TIMER2		=	0x11
#byte	T2CON		=	0x12
#byte	SSPBUF		=	0x13
#byte	SSPCON		=	0x14

long	CCPR1;

#byte	CCPR1		=	0x15	
#byte	CCPR1L		=	0x15
#byte	CCPR1H		=	0x16
#byte	CCP1CON		=	0x17
#byte	RCSTA		=	0x18
#byte	TXREG		=	0x19
#byte	RXREG		=	0x1A
#byte	CCPR2L		=	0x1B
#byte	CCPR2H		=	0x1C
#byte	CCP2CON		=	0x1D
#byte	ADRES		=	0x1E
#byte	ADCON0		=	0x1F


// Page 1 Registers
//INDF			=	0x80	:	duplicate	
#byte	OPTION		=	0x81
#byte	PCL		=	0x82
//STATUS		=	0x83	:	duplicate
//FSR			=	0x84	:	duplicate	
#byte	TRISA 		= 	0x85
#byte	TRISB 		= 	0x86
#byte	TRISC 		= 	0x87
#byte	TRISD 		= 	0x88
#byte	TRISE 		= 	0x89
//	PCLATH		=	0x8A	:	duplicate	
//	INTCON		=	0x8B	:	duplicate
#byte	PIE1		=	0x8C
#byte	PIE2		=	0x8D
#byte	PCON		=	0x8E
//				0x8F	:	reserved		
//				0x90	:	reserved	
//				0x91	:	reserved
#byte	PR2		=	0x92
#byte	SSPADD		=	0x93
#byte	SSPSTAT		=	0x94
//				0x95	:	reserved
//				0x96	:	reserved
//				0x97	:	reserved	
#byte	TXSTA		=	0x98	
#byte	SPBRG 		= 	0x99
//				0x9A	:	reserved
//				0x9B	:	reserved
//				0x9C	:	reserved
//				0x9D	:	reserved
//				0x9E	:	reserved
#byte	ADCON1		=	0x9F
#byte	EEDATA		= 0x10C
#byte	EEADR		= 0x10D
#byte	EEDATH		= 0x10E
#byte	EEADRH		= 0X10F
#byte	EECON1		= 0x18C
#byte	EECON2		= 0x18D

// option register configuration 
#define		PORTB_PULL_UP		0x80		// enable port B pull-up	
#define		EXT_INT_RISING_EDGE	0x40		// external interrupt : rising edge	
#define		WDT_EXT_CLK		0x20		// WDT clock : external clock (port_A.4)	
#define		WDT_PS			0x40		// WDT prescaler
#define		WDT_PS0			0x00
#define		WDT_PS1			0x01
#define		WDT_PS2			0x02
#define		WDT_PS3			0x03
#define		WDT_PS4			0x04
#define		WDT_PS5			0x05
#define		WDT_PS6			0x06
#define		WDT_PS7			0x07

#define		portb_pullup_enable()			OPTION&=0x7f
#define		portb_pullup_disable()			OPTION|=0x80

// interrupt control register 
#define		global_interrupt_enable()		INTCON|=0x80	// enable global interrupt
#define		global_interrupt_disable()		INTCON&=0x7f	// disable global interrupt 

#define		peripheral_interrupt_enable()	INTCON|=0x40	// enable peripheral interrupt 
#define		peripheral_interrupt_disable() 	INTCON&=0xbf	// disable peripheral interrupt

#define		timer0_interrupt_enable()		INTCON|=0x20	// enable timer0 interrupt		
#define		timer0_interrupt_disable()		INTCON&=0xdf	// disable timer0 interrupt 

#define		external_interrupt_enable()		INTCON|=0x10	// enable external interrupt  
#define		external_interrupt_disable()	INTCON&=0xef	// disable external interrupt

#define		portb_change_interrupt_enable()	INTCON|=0x08	// enable port B change interrupt
#define		portb_change_interrupt_disable()	INTCON&=0xf7	// disable port B change interrupt

#define		clear_timer0_interrupt()			INTCON&=0xfb		
#define		clear_external_interrupt_flag()		INTCON&=0xfd

#define		clear_portb_change_interrupt_flag()	INTCON&=0xfe

// after peripheral interrupt enable() 

#define		PSP_interrupt_enable()				PIE1|=0x80		//  Parallel Slave Port Read/Write Interrupt Enable
#define		PSP_interrupt_disable()				PIE1&=0x7f		//  Parallel Slave Port Read/Write Interrupt Enable

#define		AD_converter_interrupt_enable()		PIE1|=0x40		//  
#define		AD_converter_interrupt_disable()	PIE1&=0xbf		//  

#define		receive_interrupt_enable()			PIE1|=0x20		// USART receive interrupt 
#define		receive_interrupt_disable()			PIE1&=0xdf		// USART receive interrupt

#define		transmit_interrupt_enable()			PIE1|=0x10		// USART transmit interrupt 
#define		transmit_interrupt_disable()		PIE1&=0xef		// USART transmit interrupt 

#define		ssp_interrupt_enable()				PIE1|=0x08		// Synchronous Serial Port Interrupt
#define		ssp_interrupt_disable()				PIE1&=0xf7		// Synchronous Serial Port Interrupt

#define		ccp1_interrupt_enable()				PIE1|=0x04		// CCP1 module interrupt 
#define		ccp1_interrupt_disable()			PIE1&=0xfb

#define		timer2_interrupt_enable()			PIE1|=0x02
#define		timer2_interrupt_disable()			PIE1&=0xfd

#define		timer1_interrupt_enable()			PIE1|=0x01		// enable timer1 interrupt 
#define		timer1_interrupt_disable()			PIE1&=0xfe

#define		clear_PSP_interrupt_flag()			PIR1&=0x7f		//  clear parallel slave port interrupt flag
#define		clear_AD_interrupt_flag()			PIR1&=0xbf		//  clear AD converter interrupt flag
#define		clear_receive_interrupt_flag()		PIR1&=0xdf		//  clear USART receive interrupt flag
#define		clear_transmit_interrupt_flag()		PIR1&=0xef		//  clear USART receive interrupt flag
#define		clear_SSP_interrupt_flag()			PIR1&=0xf7		//  clear USART receive interrupt flag
#define		clear_CCP1_interrupt_flag()			PIR1&=0xfb		//  clear CCP1 interrupt flag
#define		clear_timer2_interrupt_flag()		PIR1&=0xfd		//  clear timer2 interrupt flag
#define		clear_timer1_interrupt_flag()		PIR1&=0xfe		//  clear timer1 interrupt flag

// serial communication interface macros 
#define		transmit_enable()					TXSTA|=0x20
#define		transmit_disable()					TXSTA&=0x7f
#define		serial_port_enable()				RCSTA|=0x80
#define		serial_port_disable()				RCSTA&=0x7f	

// I/O Port

#define PORT_DATA0				PIN_D0  	// I/O
#define PORT_DATA1				PIN_D1  	// I/O
#define PORT_DARA2				PIN_D2  	// I/O
#define PORT_DATA3				PIN_D3  	// I/O
#define PORT_DATA4				PIN_D4  	// I/O
#define PORT_DATA5				PIN_D5  	// I/O
#define PORT_DATA6				PIN_D6  	// I/O
#define PORT_DATA7				PIN_D7  	// I/O

// LCD.C
#define LCD_RS					PIN_E0  	// Analog
#define LCD_CE					PIN_E1  	// OUT
#define LCD_RW					PIN_E2  	// OUT

//====================================================
//
//  FaultCode 
//
//====================================================
#define ERR_SPI_RX			51
#define ERR_SPI_CONNECT		51

#define KEY_RUN			PIN_A0
#define KEY_STOP		PIN_A1
#define KEY_SET			PIN_B0
#define KEY_RIGHT		PIN_B1
#define KEY_SAVE		PIN_B2
#define KEY_ESC			PIN_B3
#define KEY_UP			PIN_B4
#define KEY_DOWN		PIN_B5

//
#define TEST_PIN		PIN_C2  	// #17

typedef enum {BTN_NULL,BTN_RUN,BTN_STOP,BTN_UP,BTN_DOWN,BTN_RIGHT,BTN_ESC,BTN_SET,BTN_SAVE}BUTTON ;

// lcd.c
// LCD RAM Address
#define	ROW1					0			// LCD Row1 Base Address
#define	ROW2					64			// LCD Row2 Base Address
#define	ROW3					20			// LCD Row3 Base Address
#define	ROW4					84			// LCD Row4 Base Address
#define	DDRAM					0x80		// DDRAM address
#define	CGRAM					0x40		// CGRAM address
#define	COL_LEN					20

// LCD command macros
#define	CURSE_HOME				0x02		// curse home
#define	DISPLAY_OFF				0x01		// display off
#define	DISPLAY_CURSE_BLINK_ON	0x0f		// enable display/curse/blink
#define	DISPLAY_CURSE_ON		0x0e		// enable display/curse
#define	DISPLAY_ON				0x0c		// enable display
#define	CURSOR_OFF				0x0c
#define	CURSOR_BLINK_OFF		0x0e
#define	CURSOR_BLINK			0x0f
#define	LCD_Clear()				LCD_Cmd(0x01)	// clear LCD,curse home

#define COM_TEST	0
#define TEST_MODE 		0
#define MASTER_MODE		1

#define STATE_MONITOR_MODE	0
#define STATE_EDIT_MODE		1
#define STATE_TRIP_MODE		2
#define STATE_SET_MODE		3
#define STATE_RESET_MODE	4
#define STATE_TIME_MODE		5
#define STATE_ERROR_MODE	6
#define RECORD_CLEAR_MODE	7
#define SYSTEM_INIT_MODE	8
#define CHECKSUM_MODE		9
#define STATE_POSITION_MODE	10
#define STATE_SET_MODE2		11

#endif