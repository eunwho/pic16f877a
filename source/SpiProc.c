/////////////////////////////////////////////////////////////////////////
//	Project Name 	: Input for EW Inverter  
//	Fiele Name	 	: SpiProc.c
//
//  Start 			: 2007.06.03 sunday
//
///////////////////////////////////////////////////////////////////////////


// Error가 발생하면 ErrCode를 return 한다.
// str로 보내옴 string 구조로 끝에 null을 붇여서 보낼 것   
#SEPARATE
int iSpiSend(char *str)
{
	int ErrCode;
	
	int Loop;
	long lStartMsec, lTemp;
		
	gSpiRxFlag = FALSE;	 
	
	
	ErrCode=0;
	
	lStartMsec = lGetMsec();

	// wait for finishing last command string
	while(Loop){
		if (gSpiRxFlag == TRUE) Loop = FALSE;		

		lTemp = lGetDelayMsec(lStartMsec);

		if ( lTemp > 100) Loop = False;

	}
	
	// if not error Send Spi Command String
	
	if( gSpiRxFlag ) 	 
	{
		strcopy(gSpiTxBuf,Str);		
		gSpiRxFlag = FALSE;	
		
		lStartMsec = lGetMsec();
	
		while(Loop){
			if (gSpiRxFlag == TRUE) Loop = FALSE;		
			if ( lGetDelayMSec( lStartMsec) > 100) Loop = False;
		}
	}
	if(gSpiRxFlag == FALSE ) {
		strcpy(str,"- Off Line -");
		ErrCode = ERR_SPI_CONNECT;
	}
	else{ 
		strcopy(str,gSpiRxBuf);	
		if(str[0] == 'E') ErrCode = 1;
	}
	return ErrCode;
}
