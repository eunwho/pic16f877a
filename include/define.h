#ifndef		__DEFINE_H_
#define		__DEFINE_H_

#define _XTAL_FREQ 8000000

#define PORT_DATA0				RD0
#define PORT_DATA1				RD1
#define PORT_DARA2				RD2
#define PORT_DATA3				RD3
#define PORT_DATA4				RD4
#define PORT_DATA5				RD5
#define PORT_DATA6				RD6
#define PORT_DATA7				RD7

// LCD.C
#define LCD_RS					RE0   //PIN_E0  	// Analog
#define LCD_CE					RE1   //PIN_E1  	// OUT
#define LCD_RW					RE2   //PIN_E2  	// OUT

#define KEY_RUN			PORTAbits.RA0
#define KEY_STOP		PORTAbits.RA1
#define KEY_SET			PORTBbits.RB0
#define KEY_RIGHT		PORTBbits.RB1
#define KEY_SAVE		PORTBbits.RB2
#define KEY_ESC			PORTBbits.RB3
#define KEY_UP			PORTBbits.RB4
#define KEY_DOWN		PORTBbits.RB5

// #define TEST_PIN        PORTCbits.RC2
#define TEST_PIN        RC2

#define	ROW1					0			// LCD Row1 Base Address
#define	ROW2					64			// LCD Row2 Base Address
#define	ROW3					20			// LCD Row3 Base Address
#define	ROW4					84			// LCD Row4 Base Address
#define	DDRAM					0x80		// DDRAM address
#define	CGRAM					0x40		// CGRAM address
#define	COL_LEN					20

// LCD command macros
#define	CURSE_HOME				0x02		// curse home
#define	DISPLAY_OFF				0x01		// display off
#define	DISPLAY_CURSE_BLINK_ON	0x0f		// enable display/curse/blink
#define	DISPLAY_CURSE_ON		0x0e		// enable display/curse
#define	DISPLAY_ON				0x0c		// enable display
#define	CURSOR_OFF				0x0c
#define	CURSOR_BLINK_OFF		0x0e
#define	CURSOR_BLINK			0x0f
#define	LCD_Clear()				lcd_clear( )	// clear LCD,curse home

#define COM_TEST        	0
#define TEST_MODE           0
#define MASTER_MODE         1

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

#define	ERR_SCI_RX_TIME_OUT		30
#define	ERR_SCI_RXD_MISMACH		31
#define ERR_SPI_RX			51
#define ERR_SPI_CONNECT		51
#define SCI_RX_MSG_SIZE		41
#define SCI_RX_BUF_LENGTH	25

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
#define STATE_MONITOR_MODE	0
#define STATE_EDIT_MODE		1
#define STATE_TRIP_MODE		2
#define STATE_SET_MODE		3
#define STATE_RESET_MODE	4
#define STATE_TIME_MODE		5
#define STATE_ERROR_MODE	6
#define RECORD_CLEAR_MODE	7
#define SYSTEM_INIT_MODE	8
#define CHECKSUM_MODE		9
#define STATE_POSITION_MODE	10
#define STATE_SET_MODE2		11

#define ADDR_TRIP_VIEW_CODE	'1'
#define ADDR_TRIP_VIEW_MSG	'2'
#define ADDR_TRIP_VIEW_TIME	'3'
#define ADDR_TRIP_VIEW_DATA	'4'
#define ADDR_TRIP_VIEW_I	'5'
#define ADDR_TRIP_VIEW_VDC	'6'
#define ADDR_TRIP_VIEW_HZ	'7'

#define JSK		7

const int CODE_POS[9][2] ={{0,0+JSK},{0,1+JSK},{0,2+JSK},
	{0,4+JSK},{0,6+JSK},{0,7+JSK},{0,8+JSK},{0,10+JSK},{0,11+JSK}};

typedef enum {BTN_NULL,BTN_RUN,BTN_STOP,BTN_UP,BTN_DOWN,BTN_RIGHT,BTN_ESC,BTN_SET,BTN_SAVE} BUTTON;

#endif
