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
extern int WriteEeprom(char addr,char data);
extern char ReadEeprom(char addr );
extern unsigned long ulGetDelaymSec(unsigned long Start);

extern void ErrorProc(int ErrorCode);

// KeyProc.c
extern void sciRxPrintProc(void);
extern void SelectMenuPage1(void);
extern void SelectMenuPage2(void);
extern void monitor_converter(void);
extern int MonitorProc(void);
extern void RxMonitData(void);
extern int MainMenuProc(void);
extern void EditCodeDataProc(void);
extern void TripCodeDataProc(void);
extern void ReadRealTimeData(void);
extern void ResetCodeDataProc(void);
extern void RecordClearProc(void);
extern void SystemInitProc(void);

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
extern void SerialPortSetup(void);
extern int SciSend( char *SciTx);
extern void SendChar( char xmit_data);
extern void SendSciString( char *string);
extern int getSciMsg( char *);

// AutoTunning.c
extern int AutoTunningProc();


//--- TripView.c
int TripViewProc();
void TripViewMsgTimeData();
void TripViewI_V_HZ();

#endif

// End of file
