/////////////////////////////////////////////////////////////////////////
//
//	Project Name 	: Input for EW Inverter  
//	Fiele Name	 	: module.h
//
//  Start 			: 2007.08.01 wednsday
//  Finish			:  
//
///////////////////////////////////////////////////////////////////////////
//
#ifndef		__MODULE_FILES_
#define		__MODULE_FILES_

// SUB.C
#SEPARATE
void Nop();
#SEPARATE
char WriteEeprom(char addr,char data);
#SEPARATE
char ReadEeprom(char addr );
#SEPARATE
unsigned long ulGetNowCount_msec();
#SEPARATE
unsigned long ulGetDelaymSec(long Start);
#SEPARATE
void delay_msec( unsigned long);

#SEPARATE
void ErrorProc(int ErrorCode);

// KeyProc.c
#SEPARATE
int MonitorProc();
#SEPARATE
void RxMonitData();

#SEPARATE
int MainMenuProc();
#SEPARATE
void EditCodeDataProc();

#SEPARATE
void TripCodeDataProc();

#SEPARATE
void ReadRealTimeData();

//LCD.c 
#SEPARATE
void Busy();
#SEPARATE
void LCD_Cmd(int cmd);
#SEPARATE
void LCD_Initialization();
#SEPARATE
void LCD_AddrSet(int addr);
#SEPARATE
void DisplayChar(int row,int offset,char data);
#SEPARATE
void Cursor(int row,int offset,unsigned CursorCmd);
#SEPARATE
void PrintLCD(int row,int offset,char *string);


//sci.c
#SEPARATE
void SerialPortSetup();
#SEPARATE
int SciSend(char *SciTx);
#SEPARATE
void SendChar(char xmit_data);
#SEPARATE
void SendSciString(char *string);

// AutoTunning.c
#SEPARATE
int AutoTunningProc();


//--- TripView.c
#SEPARATE
int TripViewProc();
#SEPARATE
void TripViewMsgTimeData();
#SEPARATE
void TripViewI_V_HZ();

#endif

// End of file
