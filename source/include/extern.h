#ifndef		__EXTERN_H_
#define		__EXTERN_H_

extern int disp_count;
extern unsigned long secWatchDog;
extern char gSciTxBuf[16];
extern char st[21];
//extern int gFaultCode;				// Fault
extern unsigned long gulRtsCount;				// Incr Timer2 irq base Clockof system
//extern MACHINE_STATE gMachineState;
extern int lcd_x_posi;
extern int lcd_y_posi;

#endif
