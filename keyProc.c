/////////////////////////////////////////////////////////////////////////
//	Project Name 	: Lcd operator for Converter  
//	Fiele Name	 	: keyProc.c
//
//  Start 			: 2015.08.20 Thursday
//
///////////////////////////////////////////////////////////////////////////
// read data format   "9:4:123:x.xxxe-x"
// write data format  "9:6:123:1.234e-3"
#include    "./include/header.h"
#include    "./include/extern.h"

#define RETURN_SEC  10
#define KEY_IN_VIEW_SILK	1

#if KEY_IN_VIEW_SILK
BUTTON GetKey1(void){
	BUTTON KeySave;	
	if		(! KEY_STOP )	KeySave = BTN_ESC;
	else if (! KEY_UP)      KeySave = BTN_SAVE;
	else if (! KEY_DOWN )	KeySave = BTN_RIGHT;
    else if (! KEY_RIGHT)   KeySave = BTN_DOWN;		
	else if (! KEY_ESC )    KeySave = BTN_STOP;
	else if (! KEY_SAVE )   KeySave = BTN_UP;	
	else if (! KEY_SET )	KeySave = BTN_RUN;	
	else if	(! KEY_RUN )	KeySave = BTN_SET; 
	else 					KeySave = BTN_NULL;
	return KeySave;
}
#else
BUTTON GetKey1() // 실크가 보이지 않고 LCD 연결선이 꼬여 있음 
{
	BUTTON KeySave;
	
	if		(!KEY_STOP)	KeySave = BTN_STOP;
	else if (!KEY_UP) 	KeySave = BTN_UP;
	else if (!KEY_DOWN)	KeySave = BTN_DOWN;
	else if (!KEY_RIGHT) keySave = BTN_RIGHT;		
	else if (!KEY_ESC)	KeySave = BTN_ESC;
	else if (!KEY_SAVE)	KeySave = BTN_SAVE;	
	else if (!KEY_SET)	KeySave = BTN_SET;	
	else if	(!KEY_RUN)	KeySave = BTN_RUN; 
	else 						KeySave = BTN_NULL;
	
	if(KeySave != BTN_NULL)	__delay_ms(50);
	return KeySave;
}
#endif
unsigned long ulGetElapsedTime(unsigned long count){
    if( gulRtsCount < count )   return ( 65535 - count + gulRtsCount );
    else                        return  (gulRtsCount - count);
}    

extern void sciRxPrintProc(void){
    unsigned long ulTemp;
    
    int debug;
    
    if( gSciRxFlag ) {
        debug = sci_rx_msg_box[1] - '0';
        if(( debug >= 0 ) && ( debug < 4 )) printLCD(debug,0,sci_rx_msg_box + 2,20); 
        else {
            printLCD(2,0,sci_rx_msg_box,20); 
            printLCD(3,0,sci_rx_msg_box+20,20);                 
        }
        gSciRxFlag = 0;
        setTimeOutMonit = gulRtsCount;                        
    } else{
        ulTemp = ulGetElapsedTime(setTimeOutMonit);                       
        if ( ulTemp > 5000 ){
            SerialPortSetup();
            setTimeOutMonit = gulRtsCount;
        }
    }
}

BUTTON GetKey(void)
{
	BUTTON KeySave;	

	KeySave = GetKey1();

 	if( KeySave != BTN_NULL){
		__delay_ms(20);
		KeySave = GetKey1();
	}	
	if( KeySave != BTN_NULL){
		while( GetKey1()!= BTN_NULL );
		__delay_ms(10);
		secWatchDog=0;
	}
	return KeySave; 
}

//                          {"01234567890123456789"}
const char str_clear_line[21] = {"                    "};
const char msgEditAddr[21] ={"[EDIT] 000:0.000e+0 "};

void clear_line( int low )
{
	strcpy(gStr,str_clear_line); 
    printLCD(low,0,gStr,20); 
}

void CopyCode2TxMsg(int cmd)
{
	gSciTxBuf[0] = '9'; gSciTxBuf[1] = ':';
	gSciTxBuf[2] = '4'; gSciTxBuf[3] = ':';
//--- write address 
	gSciTxBuf[4] = lcdCode[0];	gSciTxBuf[5] =lcdCode[1];	
	gSciTxBuf[6] =lcdCode[2]; 	gSciTxBuf[7] = ':';
//--- write data
	gSciTxBuf[8]  =lcdCode[3]; gSciTxBuf[9]  ='.';
	gSciTxBuf[10] =lcdCode[4]; gSciTxBuf[11] =lcdCode[5];
	gSciTxBuf[12] =lcdCode[6]; 
//--- exponent part
	gSciTxBuf[13] ='e'; gSciTxBuf[14] =lcdCode[7]; 
	gSciTxBuf[15] =lcdCode[8]; 

	if( cmd == SCI_CMD_WRITE_ROM ) gSciTxBuf[2] = '6';
	else gSciTxBuf[2] = '4';				// read data		
}

void monitor_converter(void)
{
	int loopCtrl =1;
	int debug;
    int i;

    lcdCursorOff();
    unsigned long elapsedMsec;
    unsigned long setTimeOut;
    unsigned long ulTemp;
    
	BUTTON KeyIn;
    __delay_ms(200); sciRxPrintProc(); lcd_clear( );  // clear lcd
    __delay_ms(200); sciRxPrintProc(); lcd_clear( );  // clear lcd
	while( loopCtrl)
	{ 
		if( secWatchDog > 600 ){ 
            secWatchDog = 0;
            lcd_clear( );
        }
        KeyIn = GetKey();
		if		(KeyIn == BTN_SET 	){	machineState = STATE_SET_MODE; loopCtrl = 0;	return;}
		else if	(KeyIn == BTN_RUN	){	strcpy(gSciTxBuf,"9:4:905:0.000e-0"); SendSciString( gSciTxBuf );}
		else if	(KeyIn == BTN_STOP	){	strcpy(gSciTxBuf,"9:4:905:1.000e-0"); SendSciString( gSciTxBuf );}
		else if	(KeyIn == BTN_UP	){ 	strcpy(gSciTxBuf,"9:4:905:2.000e-0"); SendSciString( gSciTxBuf );}
		else if	(KeyIn == BTN_DOWN	){	strcpy(gSciTxBuf,"9:4:905:3.000e-0"); SendSciString( gSciTxBuf );}
		else{
            ulTemp = ulGetElapsedTime(elapsedMsec);           
            if(ulTemp > 500 ){
                strcpy(gSciTxBuf,"9:4:900:0.000e+0"); SendSciString( gSciTxBuf );
                elapsedMsec = gulRtsCount;
            }
        }
        sciRxPrintProc();
  	} // while loop
}


void SelectMenuPage2(void)
{
	BUTTON KeyIn;
	int loopCtrl =1;
	int selection = 1;

	lcd_clear( );
	strcpy(gStr, " - MAIN MENU -   2/2");
	printLCD(0,0,gStr,20);

	strcpy(gStr, "4 READ ADC PROC  ");
	printLCD(1,0,gStr,20);

	strcpy(gStr, "5 RECORD CLEAR ALL ");
	printLCD(2,0,gStr,20);

	strcpy(gStr, "6 SYSTEM INIT      ");
	printLCD(3,0,gStr,20);

    secWatchDog = 0;    
	while( loopCtrl )
	{
		if( secWatchDog > RETURN_SEC ){ machineState = STATE_MONITOR_MODE; return;}
		lcdCursor(selection,0,CURSOR_BLINK);

		KeyIn = GetKey();
	
		if( KeyIn == BTN_DOWN ){
			if(selection >= 3 ){ machineState = STATE_SET_MODE; return;}
			else selection ++;
		} else if( KeyIn == BTN_UP ){
            if(selection > 1 ) selection --;
		} else if ( (KeyIn == BTN_ESC) || (KeyIn == BTN_RIGHT)){ 
			machineState = STATE_SET_MODE; return;
		} else if ( KeyIn == BTN_STOP){
			machineState = STATE_MONITOR_MODE;
			return;
		} else if( KeyIn == BTN_SET){
			if(		 selection == 1) { machineState = STATE_READ_ADC; return; }
			else if( selection == 3) { machineState = SYSTEM_INIT_MODE; return; }
		}	
	}
}

void SelectMenuPage1(void)			// System 설정 메뉴
{
	BUTTON KeyIn;

	int loopCtrl =1;
	int selection = 1;

	lcd_clear( );
	strcpy(gStr, " - MAIN MENU -   1/2");   printLCD(0,0,gStr,20);
	strcpy(gStr, "1 EDIT CTRL DATA   ");    printLCD(1,0,gStr,20);
	strcpy(gStr, "2 TRIP RECORD VIEW  ");   printLCD(2,0,gStr,20);
	strcpy(gStr, "3 SYSTEM RESET     ");    printLCD(3,0,gStr,20);

    secWatchDog = 0;    
	while( loopCtrl )
	{
		if( secWatchDog > RETURN_SEC ){ machineState = STATE_MONITOR_MODE; return; }
		KeyIn = GetKey();	
        sciRxPrintProc();        
		lcdCursor(selection,0,CURSOR_BLINK);
		if( KeyIn == BTN_DOWN ){
			if(selection >= 3 ){
				machineState = STATE_SET_MODE2;
				return;
			}
			else selection ++;
		} else if( KeyIn == BTN_UP ){
			if(selection > 1 ) selection --;
		} else if (( KeyIn == BTN_RIGHT)|| (KeyIn == BTN_ESC)){ 
			machineState = STATE_SET_MODE2;
			return;
		} else if ( KeyIn == BTN_STOP){
			machineState = STATE_MONITOR_MODE;
			return;
		} else if( KeyIn == BTN_SET){
			if(		 selection == 1){ 	machineState = STATE_EDIT_MODE; return; } 
            // else if( selection == 2)	machineState = STATE_TRIP_MODE;
            else if ( selection == 3) { machineState = STATE_RESET_MODE; return;}
		}	
	}
}

void EditCodeDataProc(void)
{
	BUTTON KeyIn;

	int i;
	int loopCtrl = 1;
	int changeCode;

	lcd_clear( );

	strcpy(gStr,msgEditAddr); printLCD(0,0,gStr,20); 

	SerialPortSetup();	
	for ( i = 0; i< 9;i++) lcdCode[i] = '0';
	lcdCode[7] = '+';

	lcdCodeId = 0;
	lcdCursor(CODE_POS[lcdCodeId][0],CODE_POS[lcdCodeId][1],CURSOR_BLINK);					
    
    secWatchDog = 0;
	while( loopCtrl)
	{
		if( secWatchDog > RETURN_SEC ){ machineState = STATE_MONITOR_MODE; return;	}

        sciRxPrintProc();
        KeyIn = GetKey();
	
		changeCode = 1;
        
		lcdCursor(CODE_POS[lcdCodeId][0],CODE_POS[lcdCodeId][1],DISPLAY_CURSE_BLINK_ON);

		if ( KeyIn == BTN_ESC){
			if(lcdCodeId == 0) lcdCodeId = 8 ;
			else			lcdCodeId -- ;
		} else if ( KeyIn == BTN_SET){
			CopyCode2TxMsg(SCI_CMD_READ_DATA);
			SendSciString( gSciTxBuf );
		} else if ( KeyIn == BTN_SAVE ){	
			lcdxPosition=0; lcdyPosition=1;
			CopyCode2TxMsg(SCI_CMD_WRITE_ROM); 
			SendSciString( gSciTxBuf );
		} else if ( KeyIn == BTN_DOWN){
			if(lcdCodeId == 7 ){
				if( lcdCode[lcdCodeId] == '+') lcdCode[lcdCodeId] = '-';
				else                     lcdCode[lcdCodeId] = '+';
			} else {
				if      ( lcdCode[lcdCodeId] > '9') lcdCode[lcdCodeId] = '9';
				else if ( lcdCode[lcdCodeId] <= '0') lcdCode[lcdCodeId] = '9';
				else 						  lcdCode[lcdCodeId]--;
			} 
		} else if ( KeyIn == BTN_UP ){
			if(lcdCodeId == 7 ){
				if( lcdCode[lcdCodeId] == '+') lcdCode[lcdCodeId] = '-'; 
				else					 lcdCode[lcdCodeId] = '+';	 
			} else {
				if     ( lcdCode[lcdCodeId] <  '0') 	 	lcdCode[lcdCodeId] = '0';
				else if( lcdCode[lcdCodeId] >= '9') 	 	lcdCode[lcdCodeId] = '0';
				else 								lcdCode[lcdCodeId]++;
			}
		} else if ( KeyIn == BTN_RIGHT){		
			if(lcdCodeId == 8) lcdCodeId = 0 ;
			else			lcdCodeId ++ ;	 
		} else if ( KeyIn ==  BTN_STOP){
			machineState = STATE_SET_MODE;
			loopCtrl = 0;
			return;
		} else changeCode = 0;
		if(changeCode == 1 ){
			DisplayChar(CODE_POS[lcdCodeId][0],CODE_POS[lcdCodeId][1],lcdCode[lcdCodeId]);
			lcdCursor(CODE_POS[lcdCodeId][0],CODE_POS[lcdCodeId][1],CURSOR_BLINK);				
		}
	}
}

void delay_sec(void)
{
	int i;

	for( i =0 ; i< 10 ; i++)   __delay_ms(100); 
}

void printTripHystory(signed int point)
{
}

void TripCodeDataProc(void)			// EEPROM TRIP ERROR DATA LOAD
{
}


void ResetSystemProc(void)		// 소프트 리셋
{
	BUTTON KeyIn;
    lcdCursorOff();
	lcd_clear( );
	strcpy(gStr, " SYSTEM RESET OK?  ");
	printLCD(0,0,gStr,20);
	strcpy(gStr, " YES = PRESS [RUN] ");
	printLCD(2,0,gStr,19);

	secWatchDog = 0;
	while( 1 ){
		if( secWatchDog > RETURN_SEC ){ machineState = STATE_MONITOR_MODE; return; }
		KeyIn = GetKey();

		if( KeyIn == BTN_RUN){
			lcd_clear( );
			lcdxPosition = 0, lcdyPosition = 0;
			strcpy(gSciTxBuf,"9:4:902:5.000e+0");	// eeprom init start
			SendSciString( gSciTxBuf );

			machineState = STATE_MONITOR_MODE;
			return;			
		} else if ( KeyIn == BTN_STOP){
			machineState = STATE_MONITOR_MODE;
			return;
		}
	}
}

void readAdcProc(void)		//
{
	int loopCtrl =1;
	int debug;
    int i;

    unsigned long elapsedMsec;
    unsigned long setTimeOut;
    unsigned long ulTemp;
    
	BUTTON KeyIn;

    lcdCursorOff();
	lcd_clear( );  // clear lcd
	strcpy(gStr, "[ READ ADC VALUE ]");
	printLCD(0,0,gStr,20);

	secWatchDog = 0;
	while( 1 ){
		if( secWatchDog > RETURN_SEC ){ machineState = STATE_MONITOR_MODE; return;}

        KeyIn = GetKey();
		if ( KeyIn == BTN_STOP){
			machineState = STATE_MONITOR_MODE;
			return ;
		} else{
            ulTemp = ulGetElapsedTime(elapsedMsec);           
            if(ulTemp > 500 ){
                strcpy(gSciTxBuf,"9:4:980:0.000e+0"); SendSciString( gSciTxBuf );
                elapsedMsec = gulRtsCount;
            }
        }
        sciRxPrintProc();
    }
}


void SystemInitProc(void)		// 시스템 초기화
{
	BUTTON KeyIn;
	int loopCtrl = 1;
	
	
    lcdCursorOff();
	lcd_clear( );
	strcpy(gStr, " SYSTEM INIT OK? ");
	printLCD(0,0,gStr,20);
	strcpy(gStr, " PRESS [RUN] INIT ");
	printLCD(2,0,gStr,20);

	secWatchDog = 0;
	while( loopCtrl ){
		if( secWatchDog > RETURN_SEC ){ machineState = STATE_MONITOR_MODE; return; }
		KeyIn = GetKey();

		if( KeyIn == BTN_RUN){
			lcd_clear( );
			lcdxPosition = 0, lcdyPosition = 0;
			strcpy(gSciTxBuf,"9:6:900:9.000e+1");	// SYSTEM TRDRY
			SendSciString( gSciTxBuf );
			machineState = STATE_MONITOR_MODE;
			return;			
		} else if ( KeyIn == BTN_STOP){
			machineState = STATE_EDIT_MODE;
			return;
		}
	}
}


const char DATE_POS[12] ={2,3,5,6,9,10,12,13,15,16,18,19};

void RecordClearProc(void)		// Trip Record All Clear
{

}
//--- end of keyProc.c
