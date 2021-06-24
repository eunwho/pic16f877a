#ifndef		__DEFINE_H_
#define		__DEFINE_H_

#define _XTAL_FREQ 20000000

#define TEST_PIN                RC2         // 1msec timer check 

#define L11         			RA0
#define L12         			RA1
#define L13         			RA2
#define L14         			RA3
//#define L05         			RA4
//#define L06         			RA5
//#define L07         			RA6
//#define L08         			RA7

#define L01         			RB0
#define L02         			RB1
#define L03         			RB2
#define L04         			RB3
#define L05         			RB4
#define L06         			RB5
#define L07         			RB6
#define L08         			RB7

#define L09 					RE0   //PIN_E0  	// Analog
#define L10     				RE1   //PIN_E1  	// OUT
// #define LCD_RW					RE2   //PIN_E2  	// OUT

#define DIP_SW1			PORTDbits.RD0
#define DIP_SW2  		PORTDbits.RD1
#define DIP_SW3			PORTDbits.RD2
#define DIP_SW4      	PORTDbits.RD3
#define DIP_SW5         PORTDbits.RD4
#define DIP_SW6			PORTDbits.RD5
#define DIP_SW7			PORTDbits.RD6
#define DIP_SW8         PORTDbits.RD7

#define RY01          0b00000001
#define RY02          0b00000010
#define RY03          0b00000100
#define RY04          0b00001000
#define RY05          0b00010000
#define RY06          0b00100000
#define RY07          0b01000000
#define RY08          0b10000000

#define RY09          0b00000001
#define RY10          0b00000010
#define RY11          0b00000100
#define RY12          0b00001000
#define RY13          0b00010000
#define RY14          0b00100000

#endif
