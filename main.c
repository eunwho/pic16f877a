/*
 * File:   main.c
 * Author: Soonkil Jung Dongho Power Electronics, Eunwho Power Electronics 
 *          2021.06.23 
 *
 */
// CONFIG
#include    <xc.h>
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include "./include/define.h"
#include <pic16f74.h>

int gSciRxFlag;
int gSciRxTestFlag;
int rxCount = 0;    
unsigned long powerFactor;

unsigned long secWatchDog;
unsigned long gulRtsCount;				// Incr Timer2 irq base Clockof system

unsigned char rxdFact[11] = {0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x0D,0x0A,0,0};
char rxdTestBuf[10]={0};
//char rxdDataBuf[60]={0};

const char STATUS_READ[10] = {0x74,0x41,0x06,0x32,0xED,0x0D,0x0A,0,0,0};
char str1[10] = {0};

const char RY_TABLE[3][7][2] = { 
    {{RY05, 0},{RY03,0},{RY01,0},{RY01+RY02,0},{RY01+RY02,RY11     },{RY01+RY02+RY03,RY13},{RY01+RY02+RY03+RY06,RY13}}, // below 85%
    {{RY06, 0},{RY04,0},{RY03,0},{RY03+RY04,0},{RY03+RY04, 0       },{RY04+RY05     ,RY11},{RY04+RY05+RY07+RY08,RY11}},   // below 94%
    {{RY07, 0},{RY05,0},{RY04,0},{RY05+RY06,0},{0        ,RY10+RY13},{RY06          ,RY12},{ 0       ,RY09+RY10+RY12}}   // below 94%
    }; 

void SendChar(char xmit_data);
void SerialPortSetup(void);
void SendSciString(char *string);

unsigned long ulGetDelaymSec(unsigned long Start)
{
	if( gulRtsCount < Start) return 65535 - Start + gulRtsCount;
	else 				   return gulRtsCount - Start;
}	
// end of file

void setup()
{		 	
	OPTION_REGbits.nRBPU = 0;   // portb fullup
	PORTB = 0xff;
    PORTC = 0xff;		
	
	TRISA = 0b00000000;         // X X X L14 ~ L11
	TRISB = 0b00000000;         // L08 ~ L01
	TRISC = 0b10000000;         // RX,TX,watch, X,X,X,X,X
	TRISD = 0b11111111;         // dip switch input
    ADCON1= 0b00000111;         // for PORTE DIO not analog port
	TRISE = 0b00000000;         // XXXXX,TEST_PIN,L10,L09
		
    // setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);

	OPTION_REGbits.T0CS = 0;    // internal instruction cycle clock
	//OPTION_REGbits.nRBPU = 0;    // portb pullup
	//RBPU = 1;    // internal instruction cycle clock
 
	__delay_ms(250);
	SerialPortSetup();	
   
    //T2CONbits.TOUTPS = 1 ; // divided by 2
    //T2CONbits.T2CKPS = 1 ; // Prescaled by 4
    //T2CONbits.TMR2ON = 1 ; // Timer 2 On
    
    // TMR2 = 0;
    // PR2 = 250;    

    //T2CON = 0b0 0111 100;

    T2CON = 0b01111100;

	PIE1bits.PSPIE = 0;         // off Parallel Slave Port Read/Write ;	
    PIE1bits.ADIE = 0;          // Off adc conversion interrupt
    PIE1bits.RCIE = 1;          // On UART receive interrupt
    PIE1bits.TXIE = 0;          // Off UART tx interrupt
    PIE1bits.SSPIE = 0;         // Off Synchronous Serial Port interrupt
    PIE1bits.CCP1IE = 0;        // Off CCP1 interrupt

    PIE1bits.TMR1IE = 0;        // On TMR1 Overflow interrupt
    PIE1bits.TMR2IE = 1;        // On TMR2 PR2 Match interrupt
       
    INTCONbits.T0IF = 0;        // Clear the flag
    INTCONbits.T0IE = 0;        // Enable the interrupt
    INTCONbits.PEIE = 1;        // Turn on peripheral interrupts  <-- This is needed by you
    INTCONbits.GIE = 1;         // ... and global interrupts  <-- As is this
}

// every 1 msec check receive Data;

void main()
{
    int temp,i;
    int x,y;
    unsigned long start_count,msec_count;
	
    setup();

    // char sendBuf[20]={0};
    start_count = gulRtsCount; 
    PORTB = 1;
    PORTA = 0; 
    PORTE = 0;
 
    while(1){
        msec_count = ulGetDelaymSec( start_count) ;
   
        if(msec_count > 2000 ) {
            start_count = gulRtsCount;
            //for(i=0;i < 8 ; i++) str1[i] = STATUS_READ[i];
            //SendSciString(str1); 
            //__delay_ms(10);
            
        }
        
        
        if( gSciRxFlag ){
            gSciRxFlag = 0;
            
            powerFactor = (unsigned long)( rxdFact[1] * 256 ) +  rxdFact[0]  ;
            
            rxdFact[0] = (unsigned char)((powerFactor / 100) + 0x30);
            rxdFact[1] = (unsigned char)(((powerFactor % 100)/10)   + 0x30);
            rxdFact[2] = (unsigned char)((powerFactor % 10) + 0x30);
            rxdFact[3] = '\r';
            rxdFact[4] = '\n';
            
            for(i=0;i <5 ; i++ ) SendChar( rxdFact[i]);
 
            if      (powerFactor < 851 ) PORTB = 1;
            else if (powerFactor < 941 ) PORTB = 3;
            else if (powerFactor < 971 ) PORTB = 7;
            else                         PORTB = 7; 
/*
            if      (DIP_SW7) y = 6;
            else if (DIP_SW6) y = 5;
            else if (DIP_SW5) y = 4;
            else if (DIP_SW4) y = 3;
            else if (DIP_SW3) y = 2;
            else if (DIP_SW2) y = 1;
            else if (DIP_SW1) y = 0;
            else              y = 10;

            if( y < 7 ) { 
                PORTB = 
                PORTA = RY_TABLE[x][y][1] >> 2; 
                PORTE = RY_TABLE[x][y][1];

            }    
*/
        }
    }
}


void __interrupt() interruptServiceRoutine()
{
	static long watchdog=0;
    static unsigned long ulTemp;
    static int checkCount;
    static int rxdStartFlag=0;
    static int rxdTestCount = 0;
    
    static int testFlag=0;
    
    static int rxTickCount=0;
    char char1;
    int i ;
     
    if(PIR1bits.TMR2IF){    
        asm("   CLRWDT  "); // CLRWDT 
        gulRtsCount ++;     watchdog ++;
        if(watchdog  > 1000){ watchdog = 0; secWatchDog++; }
        TEST_PIN = (TEST_PIN) ? 0 : 1 ;
        PIR1bits.TMR2IF=0;
        // TMR2IF = 0;        // On TMR1 Overflow interrupt
    }

    if(PIR1bits.RCIF == 1)        
    {
        char1 = RCREG;
      
        if ( char1 == 0x74 ) {
            rxdTestBuf[0] = char1;
            testFlag=1;
            checkCount = 0;
        } 
        
        if(testFlag){
            rxdTestBuf[checkCount] = char1;
            checkCount ++;
            
            if(checkCount == 4){
                if((rxdTestBuf[0]==0x74)&&(rxdTestBuf[1]==0x41)&&(rxdTestBuf[2]==0x44)&&(rxdTestBuf[3]==0x32)){
                //if((rxdTestBuf[0]==0x74)&&(rxdTestBuf[1]==0x41)){
                    rxCount = 3 ; rxdStartFlag = 1; 
                    //for( i = 0; i < 7 ; i++) rxdFact[i] = 0X01;                                    
                } else { 
                    testFlag = 0;
                    // no rxCount = 0;
                    checkCount = 0;
                    for( i = 0; i < 4 ; i++) rxdTestBuf[i] = 0X00;                                    
                }
            } 
            
        }
 
        if( rxdStartFlag == 1 ){
            rxCount ++;
            // gSciRxFlag = 1;
            
            if( rxCount == 53) rxdFact[0] = char1;
            if( rxCount == 54) rxdFact[1] = char1;
            if( rxCount == 55) rxdFact[2] = char1;
            if( rxCount == 56) rxdFact[3] = char1;
            if( rxCount == 57) rxdFact[4] = char1;
            if( rxCount == 58) rxdFact[5] = char1;
            
            if(rxCount == 68 ){
                if (char1 == 0x1A) gSciRxFlag = 1;   
                rxdFact[6] = (unsigned char)rxCount; 
                rxdStartFlag = 0;
                rxCount = 0;
            }else if(rxCount > 68){
                rxdStartFlag = 0;
                rxCount = 0;                
            }
        }        
        PIR1bits.RCIF = 0; // clear rx flag
    }
}


void SerialPortSetup(void)
{
	TXSTA=0;
	RCSTA=0;	

//	SPBRG = 129;         			// 9600
	SPBRG = 32;         			// 38400
	
	TXSTA=0b00000100;		// TX : disable,8bit data, Asynchronous mode, 16x mode
	RCSTA=0b10011000;//RCSTA=0b10010000;		// RX : disable, clear error
	TXSTAbits.TXEN = 1;     // transmit_enable();    
}

void SendChar(char xmit_data)
{
	unsigned long mCount1=0;
	unsigned long count1;

	count1 = gulRtsCount; 
    
 	while (!(TXSTAbits.TRMT) && (mCount1 < 3 )){ 		// wait untill transmit buffer is empty
		 mCount1 = ulGetDelaymSec( count1);
	 }

	TXREG = xmit_data;		// send character
	count1 = gulRtsCount; 
	mCount1= 0;

 	while (!(TXSTAbits.TRMT) && (mCount1 < 3 )){ 		// wait untill transmit buffer is empty
		 mCount1 = ulGetDelaymSec( count1);
	 }
}
// -- end of file by Soonkil jung 2021.06.23 Friday