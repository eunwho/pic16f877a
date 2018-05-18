#ifndef		__EXTERN_H_
#define		__EXTERN_H_

extern char lcdOut[21];

extern int machineState;
extern unsigned long secWatchDog;

extern int lcdCodeId;
extern char lcdCode[12];

extern char gSciTxBuf[16];
extern char gStr[SCI_RX_MSG_SIZE];
extern unsigned long gulRtsCount;				// Incr Timer2 irq base Clockof system

extern int lcdxPosition;
extern int lcdyPosition;
extern int disp_count;

extern int sci_rx_msg_start;
extern int sci_rx_msg_end;
extern char sci_rx_msg_box[SCI_RX_MSG_SIZE];
extern char Trip_Message[21];

extern char Flag_Btn;		// Trip Page Flag
extern char Flag_Set;		// Select Control Flag for Set button
extern char Flag_Start;	// Text Output Toggle Flag
extern char Flag_Page;		// Menu Page
extern char Flag_Time;		// 
extern char Trip_Header[];
extern char Trip_Error;
extern char Error_y_posi;
extern char Error_x_posi;
extern char Time_Count;
extern signed char Time_Set_Number;

extern unsigned long secWatchDog;
extern char gSciTxBuf[16];
extern int lcdxPosition;
extern int lcdyPosition;

#endif
