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
extern void RecordClearProc();
extern void SystemInitProc();

//LCD.c 
extern void lcd_write(unsigned char c);
extern void lcd_puts(const char * s);
extern void lcd_goto(unsigned char pos);
extern void lcd_putch(char c);
extern void lcd_init(void);
extern void lcd_clear(void);
extern void lcdCursorOff(void);
extern void printLCD(int row,int offset,char *string,int len);
extern void DisplayChar(int row, int offset, char c);
extern void lcdCursor(int row, int offset, unsigned char CursorCmd);

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
