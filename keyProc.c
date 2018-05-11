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
BUTTON GetKey1(){
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
BUTTON GetKey1() // ��ũ�� ������ �ʰ� LCD ���ἱ�� ���� ���� 
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


BUTTON GetKey( )
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
	strcpy(gStr,str_clear_line); printLCD(low,0,gStr); 
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

void monitor_converter()
{
	int loopCtrl =1;
	int debug;

	BUTTON KeyIn;


	LCD_Cmd(0x01);  // clear lcd
	LCD_Cmd(CURSOR_OFF);

	while( loopCtrl)
	{ 
		KeyIn = GetKey();
		lcdyPosition = 1; lcdxPosition = 0;

		debug =getSciMsg(gStr); 		
		if( debug ) {
			if(debug > 19 ); gStr[19] = 0;
			printLCD(lcdyPosition,lcdyPosition,gStr);
		}

		if		( KeyIn == BTN_SET 	){	machineState = STATE_SET_MODE; loopCtrl = 0;	return;}
		else if	(KeyIn == BTN_RUN	){	strcpy(gSciTxBuf,"9:4:905:0.000e-0"); SendSciString( gSciTxBuf );}
		else if	(KeyIn == BTN_STOP	){	strcpy(gSciTxBuf,"9:4:905:1.000e-0"); SendSciString( gSciTxBuf );}
		else if	(KeyIn == BTN_UP	){ 	strcpy(gSciTxBuf,"9:4:905:2.000e-0"); SendSciString( gSciTxBuf );}
		else if	(KeyIn == BTN_DOWN	){	strcpy(gSciTxBuf,"9:4:905:3.000e-0"); SendSciString( gSciTxBuf );}
		else{
			if( disp_count == 0){ 
				lcdyPosition = 0; lcdxPosition = 0;
				strcpy(gSciTxBuf,"9:4:901:0.000e-0");
			}
			else if( disp_count == 1){
				lcdyPosition = 0; lcdxPosition = 10;
				strcpy(gSciTxBuf,"9:4:902:0.000e-0");	// Power Input
			}	
			else if( disp_count == 2){
				lcdyPosition = 2; lcdxPosition = 0;
				strcpy(gSciTxBuf,"9:4:902:1.000e-0");	// Vdc
			}
			else if( disp_count == 3){
				lcdyPosition = 2; lcdxPosition = 10;
				strcpy(gSciTxBuf,"9:4:902:2.000e-0");	// I RMS Source 
			}
			else if( disp_count == 4){
				lcdyPosition = 3; lcdxPosition = 0;
				strcpy(gSciTxBuf,"9:4:902:3.000e-0");	// I alpa
			}
			else {
				lcdyPosition = 3; lcdxPosition = 10;
				strcpy(gSciTxBuf,"9:4:902:4.000e-0");	// I beta
			}
			sci_rx_msg_start = sci_rx_msg_end = 0;
			SendSciString( gSciTxBuf );
			__delay_ms(50);
			debug = getSciMsg(gStr);
			if( debug ) {
				if( debug> 9);
				gStr[10] = 0;
				printLCD(lcdyPosition,lcdxPosition,gStr);
			}
			else {
				strcpy(gStr,"  ---   ");	
				gStr[0] = disp_count + '0';
				printLCD(lcdyPosition,lcdxPosition,gStr);
			}
			if(disp_count >= 5 ) disp_count = 0; 
			else disp_count ++;
		}
		__delay_ms(100);
	} // while loop
}


void SelectMenuPage2()
{
	BUTTON KeyIn;
	int loopCtrl =1;
	int selection = 1;

	LCD_Cmd(0x01);
	strcpy(gStr, " - MAIN MENU -   2/2");
	printLCD(0,0,gStr);

	DisplayChar(1, 0, '4');
	strcpy(gStr, " DATE & TIME SET  ");
	printLCD(1,2,gStr);

	DisplayChar(2, 0, '5');
	strcpy(gStr, " RECORD CLEAR ALL ");
	printLCD(2,2,gStr);

	DisplayChar(3, 0, '6');
	strcpy(gStr, " SYSTEM INIT      ");
	strcpy(gStr, " POSION VALUE TEST");
	printLCD(3,2,gStr);

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


void SelectMenuPage1()			// System ���� �޴�
{
	BUTTON KeyIn;

	int loopCtrl =1;
	int selection = 1;

	LCD_Cmd(0x01);
	strcpy(gStr, " - MAIN MENU -   1/2");
	printLCD(0,0,gStr);

	DisplayChar(1, 0, '1');
	strcpy(gStr, " EDIT CTRL DATA   ");
	printLCD(1,2,gStr);

	DisplayChar(2, 0, '2');
	strcpy(gStr, " TRIP RECORD VIEW  ");
	printLCD(2,2,gStr);

	DisplayChar(3, 0, '3');
	strcpy(gStr, " SYSTEM RESET     ");
	printLCD(3,2,gStr);


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

	

void EditCodeDataProc()
{
	BUTTON KeyIn;

	int i;
	int loopCtrl = 1;
	int changeCode;

	LCD_Cmd(0x01);

	strcpy(gStr,msgEditAddr); printLCD(0,0,gStr); 

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

		//--- write data
			gSciTxBuf[9]  ='.';	gSciTxBuf[10] ='0'; gSciTxBuf[11] ='0';	gSciTxBuf[12] ='0'; 
		//--- exponent part
			gSciTxBuf[13] ='e'; gSciTxBuf[14] ='+'; gSciTxBuf[15] ='0'; 

		//--- print code discription
			gSciTxBuf[8]  ='1';
			sci_rx_msg_start = sci_rx_msg_end = 0;
			SendSciString( gSciTxBuf );
			__delay_ms(100);
			i = getSciMsg(gStr); 
			if(i) printLCD(2,0,gStr);
			else {
				strcpy(gStr,"NO Received Data");				
				printLCD(1,0,gStr);
			}

			gSciTxBuf[8]  ='2';
			sci_rx_msg_start = sci_rx_msg_end = 0;
			// for(clearcnt = 0; clearcnt <40; clearcnt++) sci_rx_msg_box[clearcnt] = 0;
			SendSciString( gSciTxBuf ); 
			__delay_ms(100); 
			i = getSciMsg(gStr); 
			if(i) printLCD(3,0,gStr);
			else {
				strcpy(gStr,"NO Received Data");				
				printLCD(3,0,gStr);
			}
		}
		else if ( KeyIn == BTN_SAVE ){	
			lcdxPosition=0; lcdyPosition=1;
			CopyCode2TxMsg(SCI_CMD_WRITE_ROM); 
			SendSciString( gSciTxBuf );
			__delay_ms(50); getSciMsg(gStr); printLCD(1,0,gStr); // debug
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

void delay_sec()
{
	int i;

	for( i =0 ; i< 10 ; i++)   __delay_ms(100); 
}

void printTripHystory(signed int point)
{
	int temp;

    int row,offset;
    
	LCD_Cmd(0x01);  // clear lcd
	temp = point + '0';

	strcpy(gStr, "TRIP [0]");
	gStr[6] = point + '0';
	printLCD(0,0,gStr);

 	delay_sec();

	sci_rx_msg_start = sci_rx_msg_end = 0;
	strcpy(gSciTxBuf,"9:4:903:0.000e+1");	// rq trip code
	gSciTxBuf[8] = temp;

	SendSciString( gSciTxBuf );
	delay_sec();
    row = 0; offset = 10;
	if( getSciMsg(gStr)) printLCD(row,offset,gStr); // disp code
	else DisplayChar( 0 , 10, '-');

	sci_rx_msg_start = sci_rx_msg_end = 0;
	strcpy(gSciTxBuf,"9:4:903:0.500e+1");   // trip time
	gSciTxBuf[8] = temp;
	SendSciString( gSciTxBuf );
	delay_sec(); 
    
    row = 2; offset =0;
	if( getSciMsg(gStr)) printLCD(row,offset,gStr); // time
	else DisplayChar( 2 , 1, '-');

	sci_rx_msg_start = sci_rx_msg_end = 0;
	strcpy(gSciTxBuf,"9:4:903:0.600e+1");   // rq trip message
	gSciTxBuf[8] = temp;
	SendSciString( gSciTxBuf );
	delay_sec(); 
	if( getSciMsg(gStr)) printLCD(1,0,gStr); // disp message
	else DisplayChar( 1 , 1, '-');

	sci_rx_msg_start = sci_rx_msg_end = 0;
	strcpy(gSciTxBuf,"9:4:903:0.400e+1");   // trip VDC
	gSciTxBuf[8] = temp;
	SendSciString( gSciTxBuf );
	delay_sec(); 
	if( getSciMsg(gStr)) printLCD(3,0,gStr); // debug
	else{
		strcpy(gStr," -    ");   
		printLCD(3,0,gStr);
	}

	sci_rx_msg_start = sci_rx_msg_end = 0;
	strcpy(gSciTxBuf,"9:4:903:0.100e+1");   // trip data
	gSciTxBuf[8] = temp;
	SendSciString( gSciTxBuf );
	delay_sec(); 
	if( getSciMsg(gStr)) printLCD(3,10,gStr); // debug
	else DisplayChar( 3 , 10, '-');
}

void TripCodeDataProc()			// EEPROM TRIP ERROR DATA LOAD
{
	BUTTON KeyIn;
	int loopCtrl=1;
	signed int point = 0;
	int change=1;
	LCD_Cmd(0x01);
	strcpy(gStr, "TRIP [0]");
	printLCD(0,0,gStr);

	strcpy(gStr, "          ");
	printLCD(0,10,gStr);

	DisplayChar(1, 0, '1');
	strcpy(gStr, " TRIP DESCIPTION ");
	printLCD(1,2,gStr);

	DisplayChar(2, 0, '2');
	strcpy(gStr, " RECORD DATE  ");
	printLCD(2,2,gStr);

	strcpy(gStr, "VDC=      ");
	printLCD(3,0,gStr);

	strcpy(gStr, "DATA=     ");
	printLCD(3,10,gStr);

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


void ResetCodeDataProc()		// ����Ʈ ����
{
	BUTTON KeyIn;

	LCD_Cmd(0x01);
	strcpy(gStr, " SYSTEM RESET OK?  ");
	printLCD(0,0,gStr);
	strcpy(gStr, " YES = PRESS [RUN]");
	printLCD(2,3,gStr);

	while( 1 ){
		KeyIn = GetKey();

		if( KeyIn == BTN_RUN){
			LCD_Cmd(0x01);
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


void SystemInitProc()		// �ý��� �ʱ�ȭ
{
	BUTTON KeyIn;
	int loopCtrl = 1;
	
	
	LCD_Cmd(0x01);
	strcpy(gStr, "SYSTEM INIT OK?");
	printLCD(0,0,gStr);
	strcpy(gStr, "PRESS RUN RESET");
	printLCD(2,3,gStr);

	while( loopCtrl ){
		KeyIn = GetKey();

		if( KeyIn == BTN_RUN){
			LCD_Cmd(0x01);
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

void RecordClearProc()		// Trip Record All Clear
{
	BUTTON KeyIn;
	int loopCtrl =1;

	strcpy(gStr, " REC CLEAR ALL! OK? ");
	printLCD(0,0,gStr);
	strcpy(gStr, " YES     NO     ");
	printLCD(2,3,gStr);

	while(loopCtrl){
		KeyIn = GetKey();
		if( KeyIn == BTN_RUN){
			lcdxPosition = 0;
			lcdyPosition = 0;
			LCD_Cmd(0x01);  // clear lcd
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