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


// read data format   "0123456789012345"
// read data format   "9:4:123:x.xxxe-x"
// write data format  "9:6:123:1.234e-3"

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

//01234567890123456789
//[TRIP]    EUNWHO.P.E
//Io:000.0A  Vo:000.0V
//Po:000.0kW Vd:000.0V
//T_CODE: 000  
// UNDER VOLT

//          Io   Vo     Po   Vdc
//[TRIP] ,000.0,000.0,000.0,000.0,

void monitSystem(char * strIn){
    int i,len;
   
    strncpy(lcdOut,strIn,7);
    printLCD(0,0,lcdOut,7); 

    strncpy(lcdOut,strIn+8,5);
    printLCD(1,3,lcdOut,5);

    strncpy(lcdOut,strIn+14,5);
    printLCD(1,14,lcdOut,5); 

    strncpy(lcdOut,strIn+21,4);
    printLCD(2,3,lcdOut,4);

    strncpy(lcdOut,strIn+26,6);
    printLCD(2,14,lcdOut,6); 

    if( *(strIn+1) == 'T' ){

        printLCD(0,7,"  E_CODE=    ",13);                

        strncpy(lcdOut,strIn+32,3);
        printLCD(0,16,lcdOut,3);
        
        strncpy(lcdOut,strIn+36,18);        
        lcdOut[19] = 0;
        printLCD(3,0,lcdOut,20); 
    }
    else{
        printLCD(3,0,"   www.eunwho.com    ",20);                
    }
}

void lcdStateName( void ){
    int i,len;
   
    // printLCD(0,0,"[WAIT] ",7);

    len = strlen(" EUNWHO P.E.");   
    printLCD(0,7," EUNWHO P.E.",len);

    printLCD(1,0,"Io:",3);
    printLCD(1,8,"A ",2);    

    printLCD(1,10,"Vo: ",4); 
    DisplayChar(1,19,'V');

    printLCD(2,0,"Po: ",3); 
    printLCD(2,7,"kW ",3);

    printLCD(2,10,"Vd: ",4); 
    DisplayChar(2,19,'V');

    printLCD(3,0,"   www.eunwho.com    ",20);                
}
unsigned long ulGetElapsedTime(unsigned long count){
    if( gulRtsCount < count )   return ( 65535 - count + gulRtsCount );
    else                        return  (gulRtsCount - count);
}    

void monitor_converter(void)
{
	int loopCtrl =1;
	int debug;

    unsigned long elapsedMsec;
    unsigned long ulTemp;
    
	BUTTON KeyIn;

	lcd_clear( );  // clear lcd
	while( loopCtrl)
	{ 
        KeyIn = GetKey();
		if		(KeyIn == BTN_SET 	){	machineState = STATE_SET_MODE; loopCtrl = 0;	return;}
		else if	(KeyIn == BTN_RUN	){	strcpy(gSciTxBuf,"9:4:905:0.000e-0"); SendSciString( gSciTxBuf );}
		else if	(KeyIn == BTN_STOP	){	strcpy(gSciTxBuf,"9:4:905:1.000e-0"); SendSciString( gSciTxBuf );}
		else if	(KeyIn == BTN_UP	){ 	strcpy(gSciTxBuf,"9:4:905:2.000e-0"); SendSciString( gSciTxBuf );}
		else if	(KeyIn == BTN_DOWN	){	strcpy(gSciTxBuf,"9:4:905:3.000e-0"); SendSciString( gSciTxBuf );}
		else{

            ulTemp = ulGetElapsedTime(elapsedMsec);           
            if(ulTemp > 500 ){
                lcdStateName();	
                sci_rx_msg_end= 0;
                strncpy(gSciTxBuf,"9:4:900:0.000e+0",strlen("9:4:900:0.000e+0"));
                SendSciString( gSciTxBuf);
            }
        }
        __delay_ms(100);
        debug =getSciMsg(gStr); 		
        if( debug ) {
            monitSystem(gStr);
            elapsedMsec = gulRtsCount;  // getCount();
        }
        else if ( ulTemp > 5000 ){
            SerialPortSetup();
            __delay_ms(100);
            elapsedMsec = gulRtsCount;
        }
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

	strcpy(gStr, "4 DATE & TIME SET  ");
	printLCD(1,0,gStr,20);

	strcpy(gStr, "5 RECORD CLEAR ALL ");
	printLCD(2,0,gStr,20);

	strcpy(gStr, "6 SYSTEM INIT      ");
	printLCD(3,0,gStr,20);

	while( loopCtrl )
	{
		lcdCursor(selection,0,CURSOR_BLINK);
		KeyIn = GetKey();
	
		if( KeyIn == BTN_DOWN ){
			if(selection >= 3 ){
				machineState = STATE_SET_MODE;
				return;
			}
			else selection ++;
		}
		else if( KeyIn == BTN_UP ){
			if(selection > 1 ) selection --;
		}
		else if ( (KeyIn == BTN_ESC) || (KeyIn == BTN_RIGHT)){ 
			machineState = STATE_SET_MODE;
			return;
		} 
		else if ( KeyIn == BTN_STOP){
			machineState = STATE_MONITOR_MODE;
			return;
		}
		else if( KeyIn == BTN_SET){
			if(		 selection == 1) machineState = STATE_TIME_MODE;
			// else if( selection == 2)	machineState = STATE_TRIP_MODE;
			// else						machineState = STATE_RESET_MODE;
			return;
		}	
	}
}

// read data format   "0123456789012345"
// read data format   "9:4:123:x.xxxe-x"
// write data format  "9:6:123:1.234e-3"

void SelectMenuPage1(void)			// System 설정 메뉴
{
	BUTTON KeyIn;

	int loopCtrl =1;
	int selection = 1;

	lcd_clear( );
	strcpy(gStr, " - MAIN MENU -   1/2");
	printLCD(0,0,gStr,20);

	// DisplayChar(1, 0, '1');
	strcpy(gStr, "1 EDIT CTRL DATA   ");
	printLCD(1,0,gStr,20);

	//DisplayChar(2, 0, '2');
	strcpy(gStr, "2 TRIP RECORD VIEW  ");
	printLCD(2,0,gStr,20);

	//DisplayChar(3, 0, '3');
	strcpy(gStr, "3 SYSTEM RESET     ");
	printLCD(3,0,gStr,20);


	while( loopCtrl )
	{
		KeyIn = GetKey();
	
		lcdCursor(selection,0,CURSOR_BLINK);
		if( KeyIn == BTN_DOWN ){
			if(selection >= 3 ){
				machineState = STATE_SET_MODE2;
				return;
			}
			else selection ++;
		}
		else if( KeyIn == BTN_UP ){
			if(selection > 1 ) selection --;
		}
		else if (( KeyIn == BTN_RIGHT)|| (KeyIn == BTN_ESC)){ 
			machineState = STATE_SET_MODE2;
			return;
		} 
		else if ( KeyIn == BTN_STOP){
			machineState = STATE_MONITOR_MODE;
			return;
		}
		else if( KeyIn == BTN_SET){
			if(		 selection == 1) 	machineState = STATE_EDIT_MODE;
			else if( selection == 2)	machineState = STATE_TRIP_MODE;
			else						machineState = STATE_RESET_MODE;
			return;
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

	while( loopCtrl)
	{

		KeyIn = GetKey();
	
		changeCode = 1;
        
		lcdCursor(CODE_POS[lcdCodeId][0],CODE_POS[lcdCodeId][1],DISPLAY_CURSE_BLINK_ON);

		if ( KeyIn == BTN_ESC){
			if(lcdCodeId == 0) lcdCodeId = 8 ;
			else			lcdCodeId -- ;
		}	
		else if ( KeyIn == BTN_SET){
			for( i = 1 ; i< 4; i++ ) clear_line(i);
			CopyCode2TxMsg(SCI_CMD_READ_DATA);

			sci_rx_msg_start = sci_rx_msg_end = 0;
			SendSciString( gSciTxBuf );
			__delay_ms(100);
			i = getSciMsg(gStr); 
			if(i){
                printLCD(1,0,gStr,9);
                printLCD(2,0,gStr+9,14);
                printLCD(3,0,gStr+24,20);
            }
			else {
				strcpy(gStr,"NO Received Data");				
				printLCD(1,0,gStr,20);
			}
		}
		else if ( KeyIn == BTN_SAVE ){	
			lcdxPosition=0; lcdyPosition=1;
			CopyCode2TxMsg(SCI_CMD_WRITE_ROM); 
			SendSciString( gSciTxBuf );
			__delay_ms(50); getSciMsg(gStr); printLCD(1,0,gStr,20); // debug
		}
		else if ( KeyIn == BTN_DOWN){
			if(lcdCodeId == 7 ){
				if( lcdCode[lcdCodeId] == '+') lcdCode[lcdCodeId] = '-';
				else                     lcdCode[lcdCodeId] = '+';
			}
			else {
				if      ( lcdCode[lcdCodeId] > '9') lcdCode[lcdCodeId] = '9';
				else if ( lcdCode[lcdCodeId] <= '0') lcdCode[lcdCodeId] = '9';
				else 						  lcdCode[lcdCodeId]--;
			}
		}
		else if ( KeyIn == BTN_UP ){
			if(lcdCodeId == 7 ){
				if( lcdCode[lcdCodeId] == '+') lcdCode[lcdCodeId] = '-'; 
				else					 lcdCode[lcdCodeId] = '+';	 
			}
			else {
				if     ( lcdCode[lcdCodeId] <  '0') 	 	lcdCode[lcdCodeId] = '0';
				else if( lcdCode[lcdCodeId] >= '9') 	 	lcdCode[lcdCodeId] = '0';
				else 								lcdCode[lcdCodeId]++;
			}
		}
		else if ( KeyIn == BTN_RIGHT){		
			if(lcdCodeId == 8) lcdCodeId = 0 ;
			else			lcdCodeId ++ ;	 
		}
		else if ( KeyIn ==  BTN_STOP){
			machineState = STATE_SET_MODE;
			loopCtrl = 0;
			return;
		}
		else changeCode = 0;
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
	int temp;

    int row,offset;
    
	lcd_clear( );  // clear lcd
	temp = point + '0';

	strcpy(gStr, "TRIP [0]");
	gStr[6] = point + '0';
	printLCD(0,0,gStr,8);

 	delay_sec();

	sci_rx_msg_start = sci_rx_msg_end = 0;
	strcpy(gSciTxBuf,"9:4:903:0.000e+1");	// rq trip code
	gSciTxBuf[8] = temp;

	SendSciString( gSciTxBuf );
	delay_sec();
    row = 0; offset = 10;
	if( getSciMsg(gStr)) printLCD(row,offset,gStr,10); // disp code
	else DisplayChar( 0 , 10, '-');

	sci_rx_msg_start = sci_rx_msg_end = 0;
	strcpy(gSciTxBuf,"9:4:903:0.500e+1");   // trip time
	gSciTxBuf[8] = temp;
	SendSciString( gSciTxBuf );
	delay_sec(); 
    
    row = 2; offset =0;
	if( getSciMsg(gStr)) printLCD(row,offset,gStr,10); // time
	else DisplayChar( 2 , 1, '-');

	sci_rx_msg_start = sci_rx_msg_end = 0;
	strcpy(gSciTxBuf,"9:4:903:0.600e+1");   // rq trip message
	gSciTxBuf[8] = temp;
	SendSciString( gSciTxBuf );
	delay_sec(); 
	if( getSciMsg(gStr)) printLCD(1,0,gStr,20); // disp message
	else DisplayChar( 1 , 1, '-');

	sci_rx_msg_start = sci_rx_msg_end = 0;
	strcpy(gSciTxBuf,"9:4:903:0.400e+1");   // trip VDC
	gSciTxBuf[8] = temp;
	SendSciString( gSciTxBuf );
	delay_sec(); 
	if( getSciMsg(gStr)) printLCD(3,0,gStr,20); // debug
	else{
		strcpy(gStr," -    ");   
		printLCD(3,0,gStr,20);
	}

	sci_rx_msg_start = sci_rx_msg_end = 0;
	strcpy(gSciTxBuf,"9:4:903:0.100e+1");   // trip data
	gSciTxBuf[8] = temp;
	SendSciString( gSciTxBuf );
	delay_sec(); 
	if( getSciMsg(gStr)) printLCD(3,10,gStr,10); // debug
	else DisplayChar( 3 , 10, '-');
}

void TripCodeDataProc(void)			// EEPROM TRIP ERROR DATA LOAD
{
	BUTTON KeyIn;
	int loopCtrl=1;
	signed int point = 0;
	int change=1;
	lcd_clear( );
	strcpy(gStr, "TRIP [0]");
	printLCD(0,0,gStr,10);

	strcpy(gStr, "          ");
	printLCD(0,10,gStr,10);

	DisplayChar(1, 0, '1');
	strcpy(gStr, " TRIP DESCIPTION ");
	printLCD(1,2,gStr,18);

	DisplayChar(2, 0, '2');
	strcpy(gStr, " RECORD DATE  ");
	printLCD(2,2,gStr,18);

	strcpy(gStr, "VDC=      ");
	printLCD(3,0,gStr,18);

	strcpy(gStr, "DATA=     ");
	printLCD(3,10,gStr,10);

	printTripHystory(0);

	lcdCursor(0,6,CURSOR_BLINK);				

	while( loopCtrl){

		KeyIn = GetKey();

		if( KeyIn == BTN_SET )	printTripHystory( point );
		else if( KeyIn  == BTN_STOP){
			machineState = STATE_SET_MODE;
			loopCtrl = 0;
			return ;
		}
		else if( KeyIn == BTN_DOWN)	point --;
		else if( KeyIn == BTN_UP)	point++;
		else 						change = 0;

		if		(point > 9) point = 0;
		else if	(point < 0 ) point = 9;

		if(change){
			DisplayChar(0,6,point+'0');
			lcdCursor(0,6,CURSOR_BLINK);				
		}
		else change = 1;
	}
}


void ResetCodeDataProc(void)		// 소프트 리셋
{
	BUTTON KeyIn;

	lcd_clear( );
	strcpy(gStr, " SYSTEM RESET OK?  ");
	printLCD(0,0,gStr,20);
	strcpy(gStr, " YES = PRESS [RUN]");
	printLCD(2,3,gStr,17);

	while( 1 ){
		KeyIn = GetKey();

		if( KeyIn == BTN_RUN){
			lcd_clear( );
			lcdxPosition = 0, lcdyPosition = 0;
			strcpy(gSciTxBuf,"9:4:902:5.000e-0");	// SYSTEM INIT
			SendSciString( gSciTxBuf );

			machineState = STATE_MONITOR_MODE;
			return;			
		}
		else if ( KeyIn == BTN_STOP){
			machineState = STATE_SET_MODE;
			return;
		}
	}
}


void SystemInitProc(void)		// 시스템 초기화
{
	BUTTON KeyIn;
	int loopCtrl = 1;
	
	
	lcd_clear( );
	strcpy(gStr, "SYSTEM INIT OK?");
	printLCD(0,0,gStr,20);
	strcpy(gStr, "PRESS RUN RESET");
	printLCD(2,3,gStr,17);

	while( loopCtrl ){
		KeyIn = GetKey();

		if( KeyIn == BTN_RUN){
			lcd_clear( );
			lcdxPosition = 0, lcdyPosition = 0;
			strcpy(gSciTxBuf,"9:4:902:5.000e-0");	// SYSTEM TRDRY
			SendSciString( gSciTxBuf );
			machineState = STATE_EDIT_MODE;
			return;
			
		}
		else if ( KeyIn == BTN_STOP){
			machineState = STATE_EDIT_MODE;
			return;
		}
	}
}


const char DATE_POS[12] ={2,3,5,6,9,10,12,13,15,16,18,19};

void RecordClearProc(void)		// Trip Record All Clear
{
	BUTTON KeyIn;
	int loopCtrl =1;

	strcpy(gStr, " REC CLEAR ALL! OK? ");
	printLCD(0,0,gStr,20);
	strcpy(gStr, " YES     NO     ");
	printLCD(2,3,gStr,17);

	while(loopCtrl){
		KeyIn = GetKey();
		if( KeyIn == BTN_RUN){
			lcdxPosition = 0;
			lcdyPosition = 0;
			lcd_clear( );  // clear lcd
			strcpy(Trip_Message, "                    ");
			strcpy(gSciTxBuf,"9:4:904:2.000e-0");
			SendSciString( gSciTxBuf );
			__delay_ms(50);
		}
		else if ( KeyIn == BTN_STOP){
			machineState = STATE_EDIT_MODE;
			return;
		}
	}
}
//--- end of keyProc.c
