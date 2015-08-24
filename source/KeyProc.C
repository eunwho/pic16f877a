/////////////////////////////////////////////////////////////////////////
//	Project Name 	: Lcd operator for Converter  
//	Fiele Name	 	: keyProc.c
//
//  Start 			: 2015.08.20 Thursday
//
///////////////////////////////////////////////////////////////////////////
// read data format   "9:4:123:x.xxxe-x"
// write data format  "9:6:123:1.234e-3"

#define KEY_IN_VIEW_SILK	1

#if KEY_IN_VIEW_SILK
#SEPARATE
BUTTON GetKey1() // 실크가 보이는 방향 
{
	BUTTON KeySave;	
	if		(!input(KEY_STOP))	KeySave = BTN_ESC;
	else if (!input(KEY_UP)) 	KeySave = BTN_SAVE;
	else if (!input(KEY_DOWN))	KeySave = BTN_RIGHT;
	else if (!input(KEY_RIGHT)) keySave = BTN_DOWN;		
	else if (!input(KEY_ESC))	KeySave = BTN_STOP;
	else if (!input(KEY_SAVE))	KeySave = BTN_UP;	
	else if (!input(KEY_SET))	KeySave = BTN_RUN;	
	else if	(!input(KEY_RUN))	KeySave = BTN_SET; 
	else 						KeySave = BTN_NULL;

	return KeySave;
}
#else
BUTTON GetKey1() // 실크가 보이지 않고 LCD 연결선이 꼬여 있음 
{
	BUTTON KeySave;
	
	if		(!input(KEY_STOP))	KeySave = BTN_STOP;
	else if (!input(KEY_UP)) 	KeySave = BTN_UP;
	else if (!input(KEY_DOWN))	KeySave = BTN_DOWN;
	else if (!input(KEY_RIGHT)) keySave = BTN_RIGHT;		
	else if (!input(KEY_ESC))	KeySave = BTN_ESC;
	else if (!input(KEY_SAVE))	KeySave = BTN_SAVE;	
	else if (!input(KEY_SET))	KeySave = BTN_SET;	
	else if	(!input(KEY_RUN))	KeySave = BTN_RUN; 
	else 						KeySave = BTN_NULL;
	
	if(KeySave != BTN_NULL)	delay_ms(50);
	return KeySave;
}
#endif

#SEPARATE
BUTTON GetKey( )
{
	BUTTON KeySave;	

	KeySave = GetKey1();

 	if( KeySave != BTN_NULL){
		delay_ms(20);
		KeySave = GetKey1();
	}	
	if( KeySave != BTN_NULL){
		while( GetKey1()!= BTN_NULL );
		delay_ms(10);
		secWatchDog=0;
	}
	return KeySave; 
}

//                          {"01234567890123456789"}
const char str_clear_line[21] = {"                    "};
const char msgEditAddr[21] ={"[EDIT] 000:0.000e+0 "};

void clear_line( int low )
{
	strcpy(st,str_clear_line); PrintLCD(low,0,st); 
}

#define JSK		7

const char CODE_POS[9][2] ={{0,0+JSK},{0,1+JSK},{0,2+JSK},
	{0,4+JSK},{0,6+JSK},{0,7+JSK},{0,8+JSK},{0,10+JSK},{0,11+JSK}};

// read data format   "0123456789012345"
// read data format   "9:4:123:x.xxxe-x"
// write data format  "9:6:123:1.234e-3"

#SEPARATE
void CopyCode2TxMsg(int cmd)
{
	gSciTxBuf[0] = '9'; gSciTxBuf[1] = ':';
	gSciTxBuf[2] = '4'; gSciTxBuf[3] = ':';
//--- write address 
	gSciTxBuf[4] = Code[0];	gSciTxBuf[5] =Code[1];	
	gSciTxBuf[6] =Code[2]; 	gSciTxBuf[7] = ':';
//--- write data
	gSciTxBuf[8]  =Code[3]; gSciTxBuf[9]  ='.';
	gSciTxBuf[10] =Code[4]; gSciTxBuf[11] =Code[5];
	gSciTxBuf[12] =Code[6]; 
//--- exponent part
	gSciTxBuf[13] ='e'; gSciTxBuf[14] =Code[7]; 
	gSciTxBuf[15] =Code[8]; 

	if( cmd == SCI_CMD_WRITE_ROM ) gSciTxBuf[2] = '6';
	else gSciTxBuf[2] = '4';				// read data		
}

#SEPARATE
void monitor_converter()
{
	BUTTON KeyIn;
	unsigned int disp_count=0;
	int loopCtrl =1;
	int debug;

	LCD_Clear();
	LCD_Cmd(CURSOR_OFF);

	while( loopCtrl)
	{ 
		KeyIn = GetKey();
		lcd_y_posi = 1; lcd_x_posi = 0;

		debug =getSciMsg(st); 		
		if( debug ) {
			if(debug > 19 ); st[19] = 0;
			printLCD(lcd_y_posi,lcd_y_posi,st);
		}

		if		( KeyIn == BTN_SET 	){	machine_state = STATE_SET_MODE; loopCtrl = 0;	return;}
		else if	(KeyIn == BTN_RUN	){	strcpy(gSciTxBuf,"9:4:905:0.000e-0"); SendSciString( gSciTxBuf );}
		else if	(KeyIn == BTN_STOP	){	strcpy(gSciTxBuf,"9:4:905:1.000e-0"); SendSciString( gSciTxBuf );}
		else if	(KeyIn == BTN_UP	){ 	strcpy(gSciTxBuf,"9:4:905:2.000e-0"); SendSciString( gSciTxBuf );}
		else if	(KeyIn == BTN_DOWN	){	strcpy(gSciTxBuf,"9:4:905:3.000e-0"); SendSciString( gSciTxBuf );}
		else{
			if( disp_count == 0){ 
				lcd_y_posi = 0; lcd_x_posi = 0;
				strcpy(gSciTxBuf,"9:4:901:0.000e-0");
			}
			else if( disp_count == 1){
				lcd_y_posi = 0; lcd_x_posi = 10;
				strcpy(gSciTxBuf,"9:4:902:0.000e-0");	// Power Input
			}	
			else if( disp_count == 2){
				lcd_y_posi = 2; lcd_x_posi = 0;
				strcpy(gSciTxBuf,"9:4:902:1.000e-0");	// Vdc
			}
			else if( disp_count == 3){
				lcd_y_posi = 2; lcd_x_posi = 10;
				strcpy(gSciTxBuf,"9:4:902:2.000e-0");	// I RMS Source 
			}
			else if( disp_count == 4){
				lcd_y_posi = 3; lcd_x_posi = 0;
				strcpy(gSciTxBuf,"9:4:902:3.000e-0");	// I alpa
			}
			else {
				lcd_y_posi = 3; lcd_x_posi = 10;
				strcpy(gSciTxBuf,"9:4:902:4.000e-0");	// I beta
			}
			sci_rx_msg_start = sci_rx_msg_end = 0;
			SendSciString( gSciTxBuf );
			delay_ms(50);
			debug = getSciMsg(st);
			if( debug ) {
				if( debug> 9);
				st[10] = 0;
				printLCD(lcd_y_posi,lcd_x_posi,st);
			}
			else {
				strcpy(st,"  ---   ");	
				st[0] = disp_count + '0';
				printLCD(lcd_y_posi,lcd_x_posi,st);
			}
			if(disp_count >= 5 ) disp_count = 0; 
			else disp_count ++;
		}
		delay_ms(100);
	} // while loop
}

#SEPARATE
void SelectMenuPage2()
{
	BUTTON KeyIn;
	int loopCtrl =1;
	int selection = 1;

	LCD_Clear();
	strcpy(st, " - MAIN MENU -   2/2");
	PrintLCD(0,0,st);

	DisplayChar(1, 0, '4');
	strcpy(st, " DATE & TIME SET  ");
	PrintLCD(1,2,st);

	DisplayChar(2, 0, '5');
	strcpy(st, " RECORD CLEAR ALL ");
	PrintLCD(2,2,st);

	DisplayChar(3, 0, '6');
	strcpy(st, " SYSTEM INIT      ");
	strcpy(st, " POSION VALUE TEST");
	PrintLCD(3,2,st);

	while( loopCtrl )
	{
		Cursor(selection,0,CURSOR_BLINK);
		KeyIn = GetKey();
	
		if( KeyIn == BTN_DOWN ){
			if(selection >= 3 ){
				machine_state = STATE_SET_MODE;
				return;
			}
			else selection ++;
		}
		else if( KeyIn == BTN_UP ){
			if(selection > 1 ) selection --;
		}
		else if ( (KeyIn == BTN_ESC) || (KeyIn == BTN_RIGHT)){ 
			machine_state = STATE_SET_MODE;
			return;
		} 
		else if ( KeyIn == BTN_STOP){
			machine_state = STATE_MONITOR_MODE;
			return;
		}
		else if( KeyIn == BTN_SET){
			if(		 selection == 1) Machine_state = STATE_TIME_MODE;
			// else if( selection == 2)	machine_state = STATE_TRIP_MODE;
			// else						machine_state = STATE_RESET_MODE;
			return;
		}	
	}
}

#SEPARATE
void SelectMenuPage1()			// System 설정 메뉴
{
	BUTTON KeyIn;

	int loopCtrl =1;
	int selection = 1;

	LCD_Clear();
	strcpy(st, " - MAIN MENU -   1/2");
	PrintLCD(0,0,st);

	DisplayChar(1, 0, '1');
	strcpy(st, " EDIT CTRL DATA   ");
	PrintLCD(1,2,st);

	DisplayChar(2, 0, '2');
	strcpy(st, " TRIP RECORD VIEW  ");
	PrintLCD(2,2,st);

	DisplayChar(3, 0, '3');
	strcpy(st, " SYSTEM RESET     ");
	PrintLCD(3,2,st);


	while( loopCtrl )
	{
		KeyIn = GetKey();
	
		Cursor(selection,0,CURSOR_BLINK);
		if( KeyIn == BTN_DOWN ){
			if(selection >= 3 ){
				machine_state = STATE_SET_MODE2;
				return;
			}
			else selection ++;
		}
		else if( KeyIn == BTN_UP ){
			if(selection > 1 ) selection --;
		}
		else if (( KeyIn == BTN_RIGHT)|| (KeyIn == BTN_ESC)){ 
			machine_state = STATE_SET_MODE2;
			return;
		} 
		else if ( KeyIn == BTN_STOP){
			machine_state = STATE_MONITOR_MODE;
			return;
		}
		else if( KeyIn == BTN_SET){
			if(		 selection == 1) 	Machine_state = STATE_EDIT_MODE;
			else if( selection == 2)	machine_state = STATE_TRIP_MODE;
			else						machine_state = STATE_RESET_MODE;
			return;
		}	
	}
}

	
#SEPARATE
void EditCodeDataProc()
{
	BUTTON KeyIn;

	int i;
	int loopCtrl = 1;
	int changeCode;

	LCD_Clear();

	strcpy(st,msgEditAddr); PrintLCD(0,0,st); 

	SerialPortSetup();	
	for ( i = 0; i< 9;i++) Code[i] = '0';
	Code[7] = '+';

	CodeID = 0;
	Cursor(CODE_POS[CodeId][0],CODE_POS[CodeId][1],CURSOR_BLINK);					

	while( loopCtrl)
	{

		KeyIn = GetKey();
	
		changeCode = 1;
		Cursor(CODE_POS[CodeID][0],CODE_POS[CodeID][1],DISPLAY_CURSE_BLINK_ON);//CURSOR_OFF);

		if ( KeyIn == BTN_ESC){
			if(CodeId == 0) CodeID = 8 ;
			else			CodeID -- ;
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
			delay_ms(100);
			i = getSciMsg(st); 
			if(i) printLCD(2,0,st);
			else {
				strcpy(st,"NO Received Data");				
				printLCD(1,0,st);
			}

			gSciTxBuf[8]  ='2';
			sci_rx_msg_start = sci_rx_msg_end = 0;
			// for(clearcnt = 0; clearcnt <40; clearcnt++) sci_rx_msg_box[clearcnt] = 0;
			SendSciString( gSciTxBuf ); 
			delay_ms(100); 
			i = getSciMsg(st); 
			if(i) printLCD(3,0,st);
			else {
				strcpy(st,"NO Received Data");				
				printLCD(3,0,st);
			}
		}
		else if ( KeyIn == BTN_SAVE ){	
			lcd_x_posi=0; lcd_y_posi=1;
			CopyCode2TxMsg(SCI_CMD_WRITE_ROM); 
			SendSciString( gSciTxBuf );
			delay_ms(50); getSciMsg(st); printLCD(1,0,st); // debug
		}
		else if ( KeyIn == BTN_DOWN){
			if(CodeID == 7 ){
				if( Code[CodeID] == '+') Code[CodeID] = '-';
				else                     Code[CodeID] = '+';
			}
			else {
				if      ( Code[CodeID] > '9') Code[CodeID] = '9';
				else if ( Code[CodeID] <= '0') Code[CodeID] = '9';
				else 						  Code[CodeID]--;
			}
		}
		else if ( KeyIn == BTN_UP ){
			if(CodeID == 7 ){
				if( Code[CodeID] == '+') Code[CodeID] = '-'; 
				else					 Code[CodeID] = '+';	 
			}
			else {
				if     ( Code[CodeID] <  '0') 	 	Code[CodeID] = '0';
				else if( Code[CodeID] >= '9') 	 	Code[CodeID] = '0';
				else 								Code[CodeID]++;
			}
		}
		else if ( KeyIn == BTN_RIGHT){		
			if(CodeId == 8) CodeID = 0 ;
			else			CodeID ++ ;	 
		}
		else if ( KeyIn ==  BTN_STOP){
			machine_state = STATE_SET_MODE;
			loopCtrl = 0;
			return;
		}
		else changeCode = 0;
		if(changeCode == 1 ){
			DisplayChar(CODE_POS[CodeID][0],CODE_POS[CodeID][1],Code[CodeID]);
			Cursor(CODE_POS[CodeID][0],CODE_POS[CodeID][1],CURSOR_BLINK);				
		}
	}
}

void delay_sec()
{
	int i;

	for( i =0 ; i< 10 ; i++)   delay_ms(100); 
}
#SEPARATE
void printTripHystory(signed int point)
{
	int temp;

	LCD_clear();
	temp = point + '0';

	strcpy(st, "TRIP [0]");
	st[6] = point + '0';
	PrintLCD(0,0,st);

 	delay_sec();

	sci_rx_msg_start = sci_rx_msg_end = 0;
	strcpy(gSciTxBuf,"9:4:903:0.000e+1");	// rq trip code
	gSciTxBuf[8] = temp;

	SendSciString( gSciTxBuf );
	delay_sec();
	if( getSciMsg(st)) printLCD(0,10,st); // disp code
	else DisplayChar( 0 , 10, '-');

	sci_rx_msg_start = sci_rx_msg_end = 0;
	strcpy(gSciTxBuf,"9:4:903:0.500e+1");   // trip time
	gSciTxBuf[8] = temp;
	SendSciString( gSciTxBuf );
	delay_sec(); 
	if( getSciMsg(st)) printLCD(2,0,st); // time
	else DisplayChar( 2 , 1, '-');

	sci_rx_msg_start = sci_rx_msg_end = 0;
	strcpy(gSciTxBuf,"9:4:903:0.600e+1");   // rq trip message
	gSciTxBuf[8] = temp;
	SendSciString( gSciTxBuf );
	delay_sec(); 
	if( getSciMsg(st)) printLCD(1,0,st); // disp message
	else DisplayChar( 1 , 1, '-');

	sci_rx_msg_start = sci_rx_msg_end = 0;
	strcpy(gSciTxBuf,"9:4:903:0.400e+1");   // trip VDC
	gSciTxBuf[8] = temp;
	SendSciString( gSciTxBuf );
	delay_sec(); 
	if( getSciMsg(st)) printLCD(3,0,st); // debug
	else{
		strcpy(st," -    ");   
		printLCD(3,0,st);
	}

	sci_rx_msg_start = sci_rx_msg_end = 0;
	strcpy(gSciTxBuf,"9:4:903:0.100e+1");   // trip data
	gSciTxBuf[8] = temp;
	SendSciString( gSciTxBuf );
	delay_sec(); 
	if( getSciMsg(st)) printLCD(3,10,st); // debug
	else DisplayChar( 3 , 10, '-');
}
#SEPARATE
void TripCodeDataProc()			// EEPROM TRIP ERROR DATA LOAD
{
	BUTTON KeyIn;
	int loopCtrl=1;
	signed int point = 0;
	int change=1;
	LCD_Clear();
	strcpy(st, "TRIP [0]");
	PrintLCD(0,0,st);

	strcpy(st, "          ");
	PrintLCD(0,10,st);

	DisplayChar(1, 0, '1');
	strcpy(st, " TRIP DESCIPTION ");
	PrintLCD(1,2,st);

	DisplayChar(2, 0, '2');
	strcpy(st, " RECORD DATE  ");
	PrintLCD(2,2,st);

	strcpy(st, "VDC=      ");
	PrintLCD(3,0,st);

	strcpy(st, "DATA=     ");
	PrintLCD(3,10,st);

	printTripHystory(0);

	Cursor(0,6,CURSOR_BLINK);				

	while( loopCtrl){

		KeyIn = GetKey();

		if( KeyIn == BTN_SET )	printTripHystory( point );
		else if( KeyIn  == BTN_STOP){
			machine_state = STATE_SET_MODE;
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
			Cursor(0,6,CURSOR_BLINK);				
		}
		else change = 1;
	}
}

#SEPARATE
void ResetCodeDataProc()		// 소프트 리셋
{
	BUTTON KeyIn;

	LCD_Clear();
	strcpy(st, " SYSTEM RESET OK?  ");
	PrintLCD(0,0,st);
	strcpy(st, " YES = PRESS [RUN]");
	PrintLCD(2,3,st);

	while( 1 ){
		KeyIn = GetKey();

		if( KeyIn == BTN_RUN){
			Lcd_Clear();
			Lcd_x_posi = 0, Lcd_y_posi = 0;
			strcpy(gSciTxBuf,"9:4:902:5.000e-0");	// SYSTEM INIT
			SendSciString( gSciTxBuf );

			machine_state = STATE_MONITOR_MODE;
			return;			
		}
		else if ( KeyIn == BTN_STOP){
			machine_state = STATE_SET_MODE;
			return;
		}
	}
}

#SEPARATE
void SystemInitProc()		// 시스템 초기화
{
	BUTTON KeyIn;
	int loopCtrl = 1;
	
	
	LCD_Clear();
	strcpy(st, "SYSTEM INIT OK?");
	PrintLCD(0,0,st);
	strcpy(st, "PRESS RUN RESET");
	PrintLCD(2,3,st);

	while( loopCtrl ){
		KeyIn = GetKey();

		if( KeyIn == BTN_RUN){
			Lcd_Clear();
			Lcd_x_posi = 0, Lcd_y_posi = 0;
			strcpy(gSciTxBuf,"9:4:902:5.000e-0");	// SYSTEM TRDRY
			SendSciString( gSciTxBuf );
			machine_state = STATE_EDIT_MODE;
			return;
			
		}
		else if ( KeyIn == BTN_STOP){
			machine_state = STATE_EDIT_MODE;
			return;
		}
	}
}


const char DATE_POS[12] ={2,3,5,6,9,10,12,13,15,16,18,19};


#SEPARATE
void TimeDataSetProc()			// 시간 설정
{
	BUTTON KeyIn;
	char ChangeCode = 0;
	int loopCtrl = 1;
	signed int point=0;
	int i;

	machine_state = STATE_TIME_MODE;
	LCD_Clear();
	strcpy(st, "DATE & TIME SETTING ");
	PrintLCD(0,0,st);

	strcpy(gSciTxBuf,"9:4:906:0.000e-0");
	SendSciString( gSciTxBuf );
	sci_rx_msg_start = sci_rx_msg_end = 0;
	delay_ms(100); 
	delay_ms(100); 
	getSciMsg(st); printLCD(1,0,st);
	printLCD(3,0,st);

	for( i = 0; i< 12 ; i++ ) Code[i] = st[ DATE_POS[i]];
	Cursor(3,DATE_POS[point],DISPLAY_CURSE_BLINK_ON);
	
	while(loopCtrl){

		ChangeCode = 1;

		KeyIn = GetKey();

		if		( KeyIn == BTN_UP  ) (Code[point])++;
		else if ( KeyIn == BTN_DOWN) (Code[point])--;
		else if ( KeyIn == BTN_ESC)		point--;
		else if	(KeyIn == BTN_RIGHT) 	point ++;
		else if ( KeyIn == BTN_STOP){
			machine_state = STATE_SET_MODE;
			return;
		}
		else if ( KeyIn == BTN_SAVE){

			strcpy(gSciTxBuf,"9:4:904:0.");
			strcpy(&(gSciTxBuf[10]),Code);
			SendSciString( gSciTxBuf );
			delay_ms(50);

			strcpy(gSciTxBuf,"9:4:904:1.");
			strcpy(&(gSciTxBuf[10]),&Code[6]);
			SendSciString( gSciTxBuf );
			strcpy(gSciTxBuf,"9:4:906:0.000e-0");
			SendSciString( gSciTxBuf );

			sci_rx_msg_start = sci_rx_msg_end = 0;
			delay_ms(50); getSciMsg(st); printLCD(1,0,st);
		}
		else if ( KeyIn == BTN_SET){
			strcpy(gSciTxBuf,"9:4:906:0.000e-0");
			SendSciString( gSciTxBuf );
			sci_rx_msg_start = sci_rx_msg_end = 0;
			delay_ms(100); 
			delay_ms(100); 
			getSciMsg(st); printLCD(1,0,st);
			printLCD(3,0,st);
		
			for( i = 0; i< 12 ; i++ ) Code[i] = st[ DATE_POS[i]];
			Cursor(3,DATE_POS[point],DISPLAY_CURSE_BLINK_ON);
		}
		else ChangeCode = 0;

		if		(point > 11) 	point = 0;
		else if (point < 0 )	point = 11;
	
		if		(Code[point] > '9') Code[point] = '0';
		else if	(Code[point] < '0') Code[point] = '9';
	
		if(ChangeCode == 1)
		{
			DisplayChar(3,DATE_POS[point],Code[point]);
			Cursor(3,DATE_POS[point],DISPLAY_CURSE_BLINK_ON);
		}
	}
}

#SEPARATE
void RecordClearProc()		// Trip Record All Clear
{
	BUTTON KeyIn;
	int loopCtrl =1;

	strcpy(st, " REC CLEAR ALL! OK? ");
	PrintLCD(0,0,st);
	strcpy(st, " YES     NO     ");
	PrintLCD(2,3,st);

	while(loopCtrl){
		KeyIn = GetKey();
		if( KeyIn == BTN_RUN){
			Lcd_x_posi = 0;
			Lcd_y_posi = 0;
			Lcd_Clear();
			strcpy(Trip_Message, "                    ");
			strcpy(gSciTxBuf,"9:4:904:2.000e-0");
			SendSciString( gSciTxBuf );
			delay_ms(50);
		}
		else if ( KeyIn == BTN_STOP){
			machine_state = STATE_EDIT_MODE;
			return;
		}
	}
}

void CheckSumErrorProc()
{
	BUTTON KeyIn;
	int loopCtrl =1;
	strcpy(st, " BACKUP RESTORE OK?");
	strcpy(st, " INIT RESTORE OK?  ");
	PrintLCD(0,0,st);
	strcpy(st, " YES     NO     ");
	PrintLCD(2,3,st);

	while(loopCtrl){
		KeyIn = GetKey();

		if ( KeyIn == BTN_ESC){
			if(Flag_Set == 1 && Flag_Start == 1)		DisplayChar(2, Flag_Set + 1, ' ' );
			else if(Flag_Set == 2 && Flag_Start == 1)	DisplayChar(2, Flag_Set + 8, ' ' );

			if(Flag_Start != 3)	Flag_Set++;
		}
		else if ( KeyIn == BTN_RIGHT){
			if(Flag_Set == 1 && Flag_Start == 1) DisplayChar(2, Flag_Set + 1, ' ' );
			else if(Flag_Set == 2 && Flag_Start == 1) DisplayChar(2, Flag_Set + 8, ' ' );
			if(Flag_Start != 3)	Flag_Set--;
		}
		else if ( KeyIn == BTN_STOP){
			machine_state = STATE_EDIT_MODE;
			return;
		}
		else if ( KeyIn == BTN_RUN){
			Flag_Btn = 2;
			if(Flag_Set == 1 && Flag_Start != 3)
			{
				Flag_Start = 3;
				strcpy(Trip_Message, "                    ");
				Lcd_Clear();
				Lcd_x_posi = 0, Lcd_y_posi = 0;
				if(Flag_Page == 3)
					strcpy(gSciTxBuf,"9:4:907:0.000e-0");
				else if(Flag_Page == 4)
					strcpy(gSciTxBuf,"9:4:907:1.000e-0");
				SendSciString( gSciTxBuf );
			}
		}
		if(Flag_Set > 2)	 Flag_Set = 1;
		else if(Flag_Set < 1) Flag_Set = 2;
	
		if(Flag_Set == 1 && Flag_Start == 1) 		DisplayChar(2, Flag_Set + 1, '*' );
		else if(Flag_Set == 2 && Flag_Start == 1)	DisplayChar(2, Flag_Set + 8, '*' );
	}
}


#SEPARATE
void PositionTestProc()
{/*
	BUTTON KeyIn;
	
	KeyIn = GetKey();

	switch(KeyIn)
	{
	case BTN_RUN:
		Lcd_x_posi = 0;
		Lcd_y_posi = 0;
		strcpy(gSciTxBuf,"9:4:905:9.000e-0");
		SendSciString( gSciTxBuf );
		break;
	case BTN_STOP:
		Lcd_x_posi = 0;
		Lcd_y_posi = 0;
		Flag_Btn = 1;
		Flag_Start = 0;
		enter_set_mode();
		break;
	default:
		break;
	}*/
}
//------------------------------
// End
//------------------------------
