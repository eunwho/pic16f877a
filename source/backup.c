/*
#SEPARATE
int iGetSciMsg(  )
{
	unsigned long ulRunTimeMsec;
	unsigned long ulStartCount;
	int iLoopCtrl;
	int iReturnVal;

	ulStartCount = ulGetNowCount_mSec();
	iLoopCtrl =1;
	gSciInFlag = 0;
	while(iLoopCtrl==1)
	{
		if(gSciInFlag == 1){
			iReturnVal = 1;
			iLoopCtrl = 0; 
		}
		else{
			ulRunTimeMsec = ulGetDelaymSec(ulStartCount);	
			if(ulRunTimeMsec > 100){
				//gSciErrFlag = 0;
				SerialPortSetup();
				Nop();
				iLoopCtrl = 0; 
				iReturnVal = 0;
			}
 		}
	}
	return iReturnVal;
}
*/

#SEPARATE	
/*
// "\0x02_A00+0.000e+09\0x03"
int iSendSciReadData(char * str)
{
	int iTemp;

	strcpy(gSciTxBuf,str);
	gSciTxBuf[1] = SCI_CMD_READ_DATA;
	iTemp = SciSend(gSciTxBuf);
	return iTemp;
}

#SEPARATE	
// 
int iSendSciCodeMsg(char * str)
{
	int iTemp;

	strcpy(gSciTxBuf,"\0x02_A00+0.000e+09\0x03");
	gSciTxBuf[2] = *(str+0);
	gSciTxBuf[3] = *(str+1);
	gSciTxBuf[4] = *(str+2);
 
	gSciTxBuf[1] = SCI_CMD_CODE_MSG;
	iTemp = SciSend(gSciTxBuf);
	return iTemp;
}
*/
#SEPARATE
char * longToAsc(char *s, signed long B)
{
	signed long A;
	
	if( B < 0){ A = - (signed long)B; *s++ = '-';}
	else 	  {	A = B ; *s++ = '+';}
	*s++ =  ( A / 10000) + '0';
	*s++ =  ( A % 10000) / 1000 + '0';
	*s++ =  ( A % 1000) / 100 + '0';
	*s++ =  ( A % 100) / 10 + '0';
	*s++ =  ( A % 10) + '0';
	*s++ =  0;
	return s;
}


//----------------------------------------------------
	for( ; ; )
	{
		gSciInFlag = 0;
		strcpy(gSciTxBuf,"_MH00+1.234e+00_");
		gSciTxBuf[0] = 0x02;					// Sci Start Byte
		gSciTxBuf[15] = 0x03;					// Sci End Byte
		iTemp = 0;
		while (iTemp == 0)
		{
			iTemp = SciSend(gSciTxBuf); //  
		}
		gSciRxBuf[SCI_RX_BUF_LENGTH-1];
		PrintLCD(2,0,gSciRxBuf+5);
		Nop();
		Nop();
		Nop();
	}
//----------------------------------------------------



	for( ; ; )
	{
		gSciInFlag = 0;
		iTemp = 0;
		while (iTemp == 0)
		{
			strcpy(SciTx,"_MM00+1.234e+0_");
			
			iTemp = SciSend( SciTx, SciRx )
		}
		Nop();
		Nop();
		Nop();
	}


	for( ; ; )
	{
		gSciInFlag = 0;
		iTemp = 0;
		while (iTemp == 0)
		{
			iTemp = iGetSciMsg( );
		}
		Nop();
		Nop();
		Nop();
	}





#INT_RDA
void SerialDataReceiveInterrupt()
{
	static int i;
	int Temp;
	
	Temp = RXREG;
	if( Temp == 2){
		i= 0;
		gSciRxBuf[0] = Temp;
		i++;
	}
	else if( Temp == 3){
		if( i == ( SCI_RX_BUF_LENGTH -1 ) ) gSCI_In_Flag = 1;
		else 								i=0; 	
	}
	else{
		if(i > (SCI_RX_BUF_LENGTH -1)) i = 0;
		else{
		  gSciRxBuf[i] = Temp;
		  i++;
		}
	}
	clear_receive_interrupt_flag();
}
/*
#INT_RDA
void SerialDataReceiveInterrupt()
{
	static int i;
	int Temp;
		
	if( i > SCI_RX_BUF_LENGTH )	i = 0;
	
	gSciRxBuf[i] = RXREG;
	if( i < SCI_RX_BUF_LENGTH )	i++;
	else{
		gSCI_In_Flag = 1;
		i =0;
	}
	clear_receive_interrupt_flag();
}
*/
/*

	for( ; ; )
	{
		gSCI_In_Flag = 0;
		while( gSCI_In_Flag == 0);	
		Nop();			
		Nop();			
		Nop();			
	}

