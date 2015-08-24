//=======================================================
//	Project Name 	: Input for EW Inverter  
//	Fiele Name	 	: AutoTunning.c
//
//  Start 			: 2008.05.27 Tuesday
//
//=======================================================

// char rom  PosMonit[8][2] = {{0,0},{0,10},{1,0},{1,10},{2,0},{2,10},{3,0},{3,10}};

#SEPARATE
int AutoTunningProc()
{
/*
	BUTTON Keyin;
	
	char SciCmd;
	int i,iTemp;
	int MonitorCode=0;		 
	int LoopCtrl,ErrorCount;
	int StateRun=0;

	LCD_Clear();
	LCD_Cmd(CURSOR_BLINK);
	ErrorCount = i = 0;

//            "01234567890123456789"
	strcpy(st, "[AOTO TUNING]       "); PrintLCD(0,0,st);
	strcpy(st, " Press [RUN]        "); PrintLCD(1,0,st);
	strcpy(st, "Rs0.1234\xf4 Rr0.1234\xf4 "); PrintLCD(2,0,st);
	strcpy(st, "Ls123.4mH Lm123.4mH "); PrintLCD(3,0,st);

	while(LoopCtrl == 1))
	{
		KeyIn = GetKey();
		if( KeyIn == BTN_STOP) LoopCtrl = 0;
		else{
			strcpy(gSciTxBuf,"\x02GC02+3.000e+00\x03");
			gSciTxBuf[1]  = SCI_CMD_WRITE_RAM;
			iTemp = SciSend(gSciTxBuf);
			if( iTemp == 0){
				strcpy(gSciTxBuf,"\x02YH00+1.234e+00\x03");
				SciCmd = SCI_CMD_START;
				gSciTxBuf[1] = SciCmd;					// Sci Start Byte
				iTemp = SciSend(gSciTxBuf);
			}
		}
	}

	if( KeyIn == BTN_STOP){
		gMachineState = STATE_MAIN_MENU;
		return 0;
	}

	iTemp = SciSend(gSciTxBuf); //  	
	if(iTemp){
		st[20]=0;
		strcpy(st,"\x7eERR RX TIME OUT !");
		PrintLCD(1,0,st);
		Cursor(1,0,CURSOR_BLINK);	
	}
	else{
		PrintLCD(1,0,gSciRxBuf[2]);
	}

	LoopCtrl = 1;	
	while(LoopCtrl)
	{
		KeyIn = GetKey();
		
//---  Go To Main Menu 
		switch(KeyIn)
		{
 		case BTN_STOP:
			gMachineState = STATE_MAIN_MENU;
			LoopCtrl = 0;
		}

//---  Monitoring 

		else if((KeyIn == BTN_NULL)&&(StateRun == 1))
		{
			gSciInFlag = 0;
			strcpy(gSciTxBuf,"\x02MH00+1.234e+00\x03");	//Monitor
			gSciTxBuf[4] = MonitorCode+'0'+1;		// Monitor Addr
			
			iTemp = SciSend(gSciTxBuf); //  
			if(iTemp){
				st[20] =0;
				strcpy(st,"\x7eERR RX TIME OUT !");
				PrintLCD(1,0,st);
				Cursor(1,0,CURSOR_BLINK);	
			}
			else{
				Nop();
				Nop();
				Nop();

				switch(MonitorCode)
				{
				case 0 : gSciRxBuf[12]=0; PrintLCD(0,10,gSciRxBuf+2); break;
				case 1 : gSciRxBuf[12]=0; PrintLCD(2,0,gSciRxBuf+2); break;
				case 2 : gSciRxBuf[12]=0; PrintLCD(2,10,gSciRxBuf+2); break;
				case 3 : gSciRxBuf[21]=0; PrintLCD(3,0,gSciRxBuf+2); break;
				case 4 : gSciRxBuf[21]=0; PrintLCD(3,10,gSciRxBuf+2); break;
				}
				MonitorCode++;
				if(MonitorCode > 3) MonitorCode = 0;
			}
		}

//----  Start & Stop Etc

		else
		{
			switch(KeyIn)
			{
			
			case BTN_RUN: 	SciCmd = SCI_CMD_START		; break; // Start
			case BTN_STOP:	SciCmd = SCI_CMD_STOP		; break; // Stop
			case BTN_ESC:	SciCmd = SCI_CMD_RESET		; break; // RESET
			case BTN_UP:	SciCmd = SCI_CMD_SPEED_UP	; break; // 속도 증가 
			case BTN_DOWN:	SciCmd = SCI_CMD_SPEED_DOWN	; break; // 속도 감속
			}

			gSciInFlag = 0;
			strcpy(gSciTxBuf,"\x02YH00+1.234e+00\x03");
			gSciTxBuf[1] = SciCmd;					// Sci Start Byte

			iTemp = SciSend(gSciTxBuf); //  	
			if(iTemp){
				st[20]=0;
				strcpy(st,"\x7eERR RX TIME OUT !");
				PrintLCD(1,0,st);
				Cursor(1,0,CURSOR_BLINK);	
			}
			else{
				PrintLCD(1,0,gSciRxBuf[2]);
			}
		}
	}
*/
//	return gFaultCode;	// debug;	
	return 0;	// debug;	
}						
//=======================================
// End of AutoTunning.c
//=======================================
						