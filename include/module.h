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
extern void Nop();
extern int WriteEeprom(char addr,char data);
extern char ReadEeprom(char addr );
extern unsigned long ulGetNowCount_msec();
extern unsigned long ulGetDelaymSec(unsigned long Start);

extern void ErrorProc(int ErrorCode);

// KeyProc.c
extern void SelectMenuPage1();
extern void SelectMenuPage2();
extern void monitor_converter();
extern int MonitorProc();
extern void RxMonitData();
extern int MainMenuProc();
extern void EditCodeDataProc();
extern void TripCodeDataProc();
extern void ReadRealTimeData();
extern void ResetCodeDataProc();
extern void TimeDataSetProc();
extern void RecordClearProc();
extern void SystemInitProc();

//LCD.c 
extern void Busy();
extern void LCD_Cmd(unsigned char cmd);
extern void LCD_Initialization();
extern void LCD_AddrSet(int addr);
extern void DisplayChar(int row,int offset,char data);
extern void lcdCursor(int row,int offset,char CursorCmd);
extern void printLCD(int row,int offset,char *string);

//sci.c
extern void SerialPortSetup();
extern int SciSend(unsigned char *SciTx);
extern void SendChar(unsigned char xmit_data);
extern void SendSciString(unsigned char *string);
extern int getSciMsg(unsigned char *);

// AutoTunning.c
extern int AutoTunningProc();


//--- TripView.c
int TripViewProc();
void TripViewMsgTimeData();
void TripViewI_V_HZ();

#endif

// End of file
