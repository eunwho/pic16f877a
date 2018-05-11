/*
 * File:   main.c
 * Author: eunwho
 *
 * Created on 2018? 5? 9? (?), ?? 4:48
 */
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)



#include "./include/header.h"
#include "./include/extern.h"
#include "./include/global.h"

void setup()
{		 	
	OPTION_REGbits.nRBPU = 0;   // portb fullup
	PORTB = 0xff;
    PORTC = 0xff;		
	
	TRISA = 0b00000011;
	TRISB = 0b01111111;
	TRISC = 0b10010000;
	TRISD = 0b00000000;
	TRISE = 0b00000000;
		
	ADCON0bits.ADON = 0;    // turn off analog module
	ADCON1bits.PCFG = 15;   // 0b00001111 PCFG3~0 all digital port

	// CMCONbits. setup_comparator(NC_NC_NC_NC);
	CMCONbits.CM = 7; 
	CMCONbits.CIS = 0; // setup_vref(FALSE);
	
    // setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);

	TMR2 = 250; // setup_timer_2(T2_DIV_BY_4,250,2);		 // 8,000,000 / (4 * 8 * (249 +1)) = 1,000 = 1/1000 sec
	T2CONbits.TOUTPS = 1 ;// post scale 2 
	T2CONbits.T2CKPS = 1 ;// pre scale by 4 ;
	T2CONbits.TMR2ON = 1 ;// enable_interrupts(INT_TIMER2);
	
	__delay_ms(100); 

	LCD_Initialization();				

	PIE1bits.PSPIE = 0;  // setup_psp(PSP_DISABLED);	
	__delay_ms(250);
	SerialPortSetup();	

	LCD_Cmd(0x01); // clear lcd
	INTCONbits.T0IE = 1 ;//enable_interrupts(INT_RDA);	
	INTCONbits.GIE = 0 ;            //enable_interrupts(GLOBAL);	

               //"01234567890123456789"
	strcpy(gStr, "DIGITAL OPERATOR    "); printLCD(0,0,gStr);
	strcpy(gStr, "[EwDo-21] v3.60     "); printLCD(1,0,gStr);
	strcpy(gStr, "EunWho Power Electro"); printLCD(2,0,gStr);
	strcpy(gStr, "TEL 82-51-262-7532  "); printLCD(3,0,gStr);
	__delay_ms(5000);
}

void main()
{

	setup();
	
	LCD_Cmd(DISPLAY_CURSE_BLINK_ON);
	machineState = STATE_MONITOR_MODE;

	while(1){

		if( secWatchDog > 60 ){
			secWatchDog = 0;
			__delay_ms(100); 
			sci_rx_msg_start = sci_rx_msg_end = 0;
			LCD_Initialization();				
			machineState = STATE_MONITOR_MODE;
			__delay_ms(100); 
		}
		if	   ( machineState == STATE_SET_MODE ) SelectMenuPage1();			
		else if( machineState == STATE_SET_MODE2 ) SelectMenuPage2();			
		else if( machineState == STATE_EDIT_MODE) EditCodeDataProc();			
		else if( machineState == STATE_TRIP_MODE) TripCodeDataProc();			
		else if( machineState == STATE_RESET_MODE) ResetCodeDataProc();		
		// else if( machineState == STATE_ERROR_MODE)	ErrorCodeDataProc();	
		else if( machineState == RECORD_CLEAR_MODE) RecordClearProc();			
		else if( machineState == SYSTEM_INIT_MODE) SystemInitProc();			
		else {   machineState = STATE_MONITOR_MODE; monitor_converter();}
	}
}


void interrupt interruptServiceRoutine()
{
	static long watchdog=0;
   	static unsigned long uartMsecCount=0;
    static unsigned long ulTemp;

    if(PIR1bits.TMR1IF){    
        CLRWDT();
        gulRtsCount ++;			// 1 msec count 
        watchdog ++;
        if(watchdog  > 1000){
            watchdog = 0;
            secWatchDog++;
        }
 
//        if( glRtsCount % 2 ) 	output_high(TEST_PIN);	// debug
//        else					output_low(TEST_PIN);	//

        PIR1bits.TMR1IF=0;
    }
    
    if(PIR1bits.TXIF == 1)
    {
//        LATCbits.LATC0=!LATCbits.LATC0;
        PIR1bits.TXIF = 0; // clear tx flag
    }

    //check if the interrupt is caused by RX pin
    if(PIR1bits.RCIF == 1)
    {
        if( gulRtsCount < uartMsecCount ) ulTemp =  65535 - uartMsecCount + gulRtsCount;
        else                              ulTemp = gulRtsCount - uartMsecCount;
     
        if( ulTemp > 200 ){ 
        	sci_rx_msg_start = sci_rx_msg_end = 0;
        }
        uartMsecCount = gulRtsCount;	
        sci_rx_msg_box[ sci_rx_msg_end ] = RCREG;
    	sci_rx_msg_end++;	
        if( sci_rx_msg_end >= SCI_RX_MSG_SIZE ) sci_rx_msg_end = 0;
        if( sci_rx_msg_start == sci_rx_msg_end ) sci_rx_msg_start ++; 
        PIR1bits.RCIF = 0; // clear rx flag
    }
}
