/////////////////////////////////////////////////////////////////////////
//
//	Project Name 	: Input for EW Inverter  
//	Fiele Name	 	: Ewdo_21.h
//
//  Start 			: 2007.06.03 sunday
//  Finish			:  
//
///////////////////////////////////////////////////////////////////////////

// I/O Port

#define PORT_DATA0				PIN_D0  	// I/O
#define PORT_DATA1				PIN_D1  	// I/O
#define PORT_DARA2				PIN_D2  	// I/O
#define PORT_DATA3				PIN_D3  	// I/O
#define PORT_DATA4				PIN_D4  	// I/O
#define PORT_DATA5				PIN_D5  	// I/O
#define PORT_DATA6				PIN_D6  	// I/O
#define PORT_DATA7				PIN_D7  	// I/O


//====================================================
//
//  FaultCode 
//
//====================================================
#define ERR_SPI_RX			51
#define ERR_SPI_CONNECT		51

#define KEY_RUN			PIN_A0
#define KEY_STOP		PIN_A1
#define KEY_SET			PIN_B0
#define KEY_RIGHT		PIN_B1
#define KEY_SAVE		PIN_B2
#define KEY_ESC			PIN_B3
#define KEY_UP			PIN_B4
#define KEY_DOWN		PIN_B5

//
#define TEST_PIN		PIN_C2  	// #17

#define RXD_STACK_LENGTH
#define Rx_Ready()		(PIR1 & 0x20)
#define Tx_Ready()		(TXSTA & 0x02)

#define SCI_RX_BUF_LENGTH	19		// 19byte를 받음 

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

#define SCI_CMD_RUN			'G'
#define SCI_CMD_STOP		'S'
#define SCI_CMD_READ		'R'
#define SCI_CMD_WRITE		'W'
#define SCI_CMD_MONITOR		'M'		// Addr에 대한 설명 등 기타 

// XA00 A00의 스트링을 요구함.   
#define SCI_CMD_MONITOR1	'X' // 스트링을 요구 첫 번째 10개 
#define SCI_CMD_MONITOR2	'Y' // 스트링을 요구 다음 10개 요구 

enum BUTTON {BTN_NULL,BTN_RUN,BTN_STOP,BTN_UP,BTN_DOWN,BTN_RIGHT,BTN_ESC,BTN_SET,BTN_SAVE};
	
