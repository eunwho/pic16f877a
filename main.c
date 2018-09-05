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
		
	ADCON0bits.ADON = 0;   // turn off analog module
	ADCON1bits.PCFG = 7;   // 0b0000011x PCFG3~0 all digital port

	// CMCONbits. setup_comparator(NC_NC_NC_NC);
	CMCONbits.CM = 7; 
	CMCONbits.CIS = 0; // setup_vref(FALSE);
	
    // setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);

	OPTION_REGbits.T0CS = 0;    // internal instruction cycle clock
 
//	TMR2 = 250; // setup_timer_2(T2_DIV_BY_4,250,2);		 // 8,000,000 / (4 * 8 * (249 +1)) = 1,000 = 1/1000 sec
//	T2CONbits.TOUTPS = 1 ;// post scale 2 
//	T2CONbits.T2CKPS = 1 ;// pre scale by 4 ;
//	T2CONbits.TMR2ON = 1 ;// enable_interrupts(INT_TIMER2);

	lcd_init();				

	__delay_ms(250);
	SerialPortSetup();	

	// setup_timer_2(T2_DIV_BY_4,250,2);		 // 8,000,000 / (4 * 8 * (249 +1)) = 1,000 = 1/1000 sec
	// set_timer2(0);
	// enable_interrupts(INT_TIMER2);
    T2CONbits.TOUTPS = 1 ; // divided by 2
    T2CONbits.T2CKPS = 1 ; // Prescaled by 4
    T2CONbits.TMR2ON = 1 ; // Timer 2 On
    
    TMR2 = 0;
    PR2 = 250;    
	lcd_clear( ); // clear lcd

	PIE1bits.PSPIE = 0;         // off Parallel Slave Port Read/Write ;	
    PIE1bits.ADIE = 0;          // Off adc conversion interrupt
    PIE1bits.RCIE = 1;          // On UART receive interrupt
    PIE1bits.TXIE = 0;          // Off UART tx interrupt
    PIE1bits.SSPIE = 0;         // Off Synchronous Serial Port interrupt
    PIE1bits.CCP1IE = 0;        // Off CCP1 interrupt

    PIE1bits.TMR2IE = 1;        // On TMR2 PR2 Match interrupt

    PIE1bits.TMR1IE = 0;        // On TMR1 Overflow interrupt
    
    INTCONbits.T0IF = 0;        // Clear the flag
    INTCONbits.T0IE = 0;        // Enable the interrupt
    INTCONbits.PEIE = 1;        // Turn on peripheral interrupts  <-- This is needed by you
    INTCONbits.GIE = 1;         // ... and global interrupts  <-- As is this
}

void displayEunwhoPE(){
               //"01234567890123456789"
	strcpy(gStr, "DIGITAL OPERATOR    "); printLCD(0,0,gStr,20);
	strcpy(gStr, "[EwDo-21] v3.60     "); printLCD(1,0,gStr,20);
	strcpy(gStr, "EunWho Power Electro"); printLCD(2,0,gStr,20);
	strcpy(gStr, "TEL 82-51-262-7532  "); printLCD(3,0,gStr,20);
	__delay_ms(500);

    lcd_clear();
	__delay_ms(500);
    
               //"01234567890123456789"
	strcpy(gStr, "DIGITAL OPERATOR    "); printLCD(0,0,gStr,20);
	strcpy(gStr, "[EwDo-21] v3.60     "); printLCD(1,0,gStr,20);
	strcpy(gStr, "EunWho Power Electro"); printLCD(2,0,gStr,20);
	strcpy(gStr, "TEL 82-51-262-7532  "); printLCD(3,0,gStr,20);
	__delay_ms(500);    
}
#define LEN_NAME_EW    40
int scrollCount = 0;
const char strEunwhoPE[] = "EUNWHO POWER ELECTRONICS www.eunwho.com  ";
//const int strLenEunwho = 39;

void main()
{
    int temp,i;
	setup();
    
//    displayEunwhoPE();
	
    machineState = STATE_MONITOR_MODE;

	while(1){

		if( secWatchDog > 60 ){
			secWatchDog = 0;
			__delay_ms(100); 
			sci_rx_msg_start = sci_rx_msg_end = 0;
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

void __interrupt() interruptServiceRoutine()
{
	static long watchdog=0;
   	static unsigned long uartMsecCount=0;
    static unsigned long ulTemp;
    char char1;
    static char sciRxBuf[21];
    int i ;
    
    if(PIR1bits.TMR2IF){    
        //clear watchdog
        // #asm 
        asm("   CLRWDT  "); // CLRWDT 
        // #endasm    
        gulRtsCount ++;			// 1 msec count 
        watchdog ++;
        if(watchdog  > 1000){
            watchdog = 0;
            secWatchDog++;
        }
        if (TEST_PIN)  TEST_PIN = 0 ;
        else           TEST_PIN = 1 ;	// debug
        PIR1bits.TMR2IF=0;
    }

    if(PIR1bits.RCIF == 1)
    {
        char1 = RCREG;
        if(char1 == 2 ){
            sci_rx_msg_end = 0;
        }else if((char1 == 3 )||(sci_rx_msg_end >= SCI_RX_MSG_SIZE)){
            for ( i = 0 ; i < sci_rx_msg_end ; i ++ ) sci_rx_msg_box[i] = sciRxBuf[i];
            sci_rx_msg_box[i+1] = 0;
            sci_rx_msg_box[i+2] = 0;
            sci_rx_msg_end = 0;
            gSciRxFlag = 1;            
        } else {
          sciRxBuf[ sci_rx_msg_end ] = char1;
          if( sci_rx_msg_end < SCI_RX_MSG_SIZE ) sci_rx_msg_end ++;
        }
        PIR1bits.RCIF = 0; // clear rx flag
    }
}
