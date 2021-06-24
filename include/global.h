#ifndef		__GLOBAL_VAR_
#define		__GLOBAL_VAR_

int gSciRxFlag;

int machineState;
unsigned long secWatchDog;
//int machine_stae;

int sciRxdNumber;
char gSciTxBuf[16];
char gStr[SCI_RX_MSG_SIZE]={0};
unsigned long gulRtsCount;				// Incr Timer2 irq base Clockof system

int sci_rx_msg_start=0;
int sci_rx_msg_end= 0;
char sci_rx_msg_box[SCI_RX_MSG_SIZE]={0};
char Trip_Message[21] = {0};

signed char Time_Set_Number = 0;
//char Header_Count = 0;
#endif
