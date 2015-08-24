/////////////////////////////////////////////////////////////////////////
//
//	Project Name 	: Input for EW Inverter  
//	Fiele Name	 	: sci.c
///////////////////////////////////////////////////////////////////////////
//
// 8Mhz  baud:38400
//
#INT_RDA
void SerialDataReceiveInterrupt( )
{
	static unsigned long msec_count=0;
//	static int rxd_count=0;

	if( ulGetDelaymSec( msec_count) > 200 ){ 
		sci_rx_msg_start = sci_rx_msg_end = 0;
	}

	msec_count = ulGetNowCount_msec();	

	sci_rx_msg_box[sci_rx_msg_end ] = RXREG;

/*
	if( sci_rx_msg_box[sci_rx_msg_end ] < 32 || sci_rx_msg_box[sci_rx_msg_end ] > 176){
		sci_rx_msg_box[sci_rx_msg_end ] = ' ';
	//	sci_rx_msg_end--;
	}
*/
	sci_rx_msg_end++;	
	if( sci_rx_msg_end >= SCI_RX_MSG_SIZE ) sci_rx_msg_end = 0;
	if( sci_rx_msg_start == sci_rx_msg_end ) sci_rx_msg_start ++; 
	clear_receive_interrupt_flag();
}

void sci_rx_msg_LCD_print_proc()
{
	char msg;
	char tCnt;
//	int count;

	if( bit_test(RCSTA,1)){ // over_run error
		bit_set(RCSTA,4);
		return;
	}

	if( bit_test(RCSTA,2)){ // framing error
		msg = RXREG; return;
	}
	if(machine_state == STATE_MONITOR_MODE && Flag_Btn == 2)
	{
		strcpy(st, "                    ");
		PrintLCD(1,0,st);
		Flag_Btn = 1;
	}
	if(Trip_error == 3 && machine_state == STATE_MONITOR_MODE)	// 마지막에 들어온 TRIP메시지 출력
	{
		PrintLCD(1,0,Trip_Message);
	//	Trip_error = 0;
	}

	if(sci_rx_msg_box[1] == '-' && sci_rx_msg_box[2] == 'C'
	&& sci_rx_msg_box[3] == 'h')
	{
		Lcd_x_posi = 0, Lcd_y_posi = 0;
	}

	if(sci_rx_msg_box[1] == 'B' && sci_rx_msg_box[2] == 'R'
	&& sci_rx_msg_box[3] == 'E')
	{
		machine_state = CHECKSUM_MODE;
		Flag_Page = 3;
		Lcd_Clear();
		return;
	}
	if(sci_rx_msg_box[1] == 'I' && sci_rx_msg_box[2] == 'R'
	&& sci_rx_msg_box[3] == 'E')
	{
		machine_state = CHECKSUM_MODE;
		Flag_Page = 4;
		Lcd_Clear();
		return;
	}

	// TRIP ERROR 헤더 검사
	if(sci_rx_msg_box[1] == 'T')
	{
		Trip_Header[0] = sci_rx_msg_box[1];
		Trip_Header[1] = sci_rx_msg_box[2];
		Trip_Header[2] = sci_rx_msg_box[3];
	}
	if(Trip_Header[0] == 'T' && Trip_Header[1] == 'R'	// TRIP ERROR 신호가 올 경우
	&& Trip_Header[2] == 'P')
	{
		Trip_Header[0]=' ';								// TRIP 헤더 초기화
		Trip_Header[1]=' ';
		Trip_Header[2]=' ';
		lcd_x_posi = 0;
		lcd_y_posi = 0;
		Error_x_posi = 0;
		Error_y_posi = 0;
		Trip_Error = 1;
//		machine_state = STATE_ERROR_MODE;				// TRIP ERROR MODE
		strcpy(Trip_Message, "                    ");
		Lcd_Clear();
		return;
	}

	if(Flag_Time == 1)
	{
		for(tCnt = 0; tCnt < 20; tCnt++)
		{
			if(tCnt != 10 && tCnt != 11)
				st[tCnt] = sci_rx_msg_box[tCnt + 1];
		}
		Time_Set_Number = sci_rx_msg_box[3] - '0';

	//	Lcd_Clear();
		PrintLCD(2,0,st);
		Delay_ms(50);
	//	PrintLCD(0,0,sci_rx_msg_box+1);
		Flag_Time = 2;
	//	return;
	}

//	count = 0;
/*
		if(count > 20){				  
			sci_rx_msg_start = sci_rx_msg_end = 0;
			break;
		}
*/

//	while( sci_rx_msg_start != sci_rx_msg_end && Flag_Time != 2 && count <= 39 )
	while( sci_rx_msg_start != sci_rx_msg_end && Flag_Time != 2 )
	{
		msg = sci_rx_msg_box[sci_rx_msg_start];
	
		if( sci_rx_msg_start >= SCI_RX_MSG_SIZE ) sci_rx_msg_start = 0;
		
		if(Trip_Error == 0 || Trip_Error == 3)
			DisplayChar(lcd_y_posi,lcd_x_posi, msg ); // 문자 출력

		if( lcd_x_posi >= 19 ){
			lcd_x_posi = 0; 
			if( lcd_y_posi >= 3)lcd_y_posi = 1;
			else 				lcd_y_posi ++;
		}
		else lcd_x_posi ++;
		
		if(Trip_Error == 1 && sci_rx_msg_start != 0)			// Trip 모드(EEPROM DATA LOAD) , Trip Error 모드시
		{
			if(msg < 32 ){nop();}
			else if(sci_rx_msg_start >16 && Error_y_posi == 0)	// Error메시지 16자 까지만 출력
				return;
			else{
				if(Error_y_posi == 0){
					if(Error_x_posi > 5 && msg == '2'){
						Error_x_posi = 0; Error_y_posi++;
					}
				}
				if(Error_y_posi < 4 && Error_x_posi < 20 && sci_rx_msg_start != 0)
					DisplayChar(Error_y_posi,Error_x_posi, msg );
				if(Error_y_posi == 0 && Error_x_posi > 3 && machine_state != STATE_TRIP_MODE)
					Trip_Message[Error_x_posi - 4] = msg;	// TRIP 메시지 저장
						
				if(Error_x_posi >= 19){
					Error_x_posi = 0;
					if( Error_y_posi >= 4)	Error_y_posi = 0;
					else					Error_y_posi ++;
				}
				else Error_x_posi++;
			}
		}
	}
}

int getSciMsg(char * str)
{
	int count = 0;

	while( sci_rx_msg_start != sci_rx_msg_end && count < 20 )
	{		
		*(str ++) = sci_rx_msg_box[sci_rx_msg_start ++ ];
		if( sci_rx_msg_start >= SCI_RX_MSG_SIZE ) sci_rx_msg_start = 0;		
		count ++;
	}
	*str = 0;
	return count;
}

#SEPARATE
void SerialPortSetup()
{
	//통신 포터 초기화
	TXSTA=0;
	RCSTA=0;	
	
	// port 설정 port_C.7=RX --> input, port_C.6=TX --> output
	TRISC=0b10010000;	// debug

	SPBRG = 12;//SPBRG=12;			// 38400
	
	TXSTA=0b00000100;		// TX : disable,8bit data, Asynchronous mode, 16x mode
	// serial_port_enable();
	RCSTA=0b10011000;//RCSTA=0b10010000;		// RX : disable, clear error
	transmit_enable();
}

#SEPARATE
void SendChar(char xmit_data)
{
	unsigned long msec_count=0;
	unsigned long start_count;

	start_count = ulGetNowCount_msec();
 	while ((!TX_Ready()) && (msec_count < 2 )){ 		// wait untill transmit buffer is empty
		 msec_count = ulGetDelaymSec( start_count);
		Nop();
		Nop();
	 }

	TXREG=xmit_data;		// send character

	start_count = ulGetNowCount_msec();
	msec_count= 0;

 	while ((!TX_Ready()) && (msec_count < 2 )){ 		// wait untill transmit buffer is empty
		 msec_count = ulGetDelaymSec( start_count);
		Nop();
		Nop();

	 }
}

#SEPARATE
void SendSciString(char *string)
{
	int count=0;
	while ((*string) && (count < 40)) {
		SendChar(*(string++));
		count++;
	}
}
//=========================================
// End of sci.c
//=========================================