/////////////////////////////////////////////////////////////////////////
//
//	Project Name 	: Input for EW Inverter  
//	Fiele Name	 	: sci.h
//
//  Start 			: 2007.08.01 wednsday
//  Finish			:  
//	Edit 			: 2008.05.21
///////////////////////////////////////////////////////////////////////////
//
// 8Mhz  baud:19600 high speed
//

//#define RXD_STACK_LENGTH
#define Rx_Ready()		(PIR1 & 0x20)
#define Tx_Ready()		(TXSTA & 0x02)

#define SCI_RX_MSG_SIZE		30
//#define SCI_RX_BUF_LENGTH	25

#define SCI_HEAD 			2
#define SCI_END  			3

#define SCI_CMD_BYTE		1
#define SCI_ADDR0			2
#define SCI_ADDR1			3
#define SCI_ADDR2			4

#define SCI_DATA0			5
#define SCI_DATA1			6
#define SCI_DATA2			7
#define SCI_DATA3			8
#define SCI_DATA4			9

#define SCI_CMD_START		0x41	//'A'
#define SCI_CMD_STOP		0x42	//'B'
#define SCI_CMD_RESET		0x43	//'C'
#define SCI_CMD_SPEED_UP	0x44	//'D'	
#define SCI_CMD_SPEED_DOWN	0x45	//'E'
#define SCI_CMD_READ_DATA	0x46	//'F'
#define SCI_CMD_WRITE_RAM	0x47	//'G'
#define SCI_CMD_WRITE_ROM	0x48	//'H'
#define SCI_CMD_READ_ALL	0x49	//'I'
#define SCI_CMD_WRITE_ALL	0x4A	//'J'
#define SCI_CMD_CODE_MSG	0x4B	//'K'
#define SCI_CMD_WRITE_CHECK	0x4C	//'L'
#define SCI_CMD_MONITOR		0x4D	//'M'
#define SCI_CMD_TIMER		0x4E	//'N'
#define SCI_CMD_TRIP_VIEW	0x4F	//'O'
#define SCI_CMD_TX_RESET	0x50	//'P'
#define SCI_CMD_BTN_SAVE	0x51	//'Q'
#define SCI_CMD_INIT_DATA	0x52	//'R'

#define	STATE_READY				'0'
#define	STATE_RUN				'1'
#define	STATE_TRIP				'2'
#define	STATE_INIT_RUN			'3'
#define	STATE_GO_STOP			'4'
#define	STATE_WAIT_BREAK_OFF	'5'

//========================================
// End of sci.h
//========================================