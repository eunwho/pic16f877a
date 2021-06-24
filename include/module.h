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
extern unsigned long ulGetDelaymSec(unsigned long Start);

//sci.c
extern void SerialPortSetup(void);
extern int SciSend( char *SciTx);
extern void SendChar( char xmit_data);
extern void SendSciString( char *string);

#endif

// End of file
