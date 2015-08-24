/////////////////////////////////////////////////////////////////////////
//	Project Name 	: Input for EW Inverter  
//	File Name	 	: main.c
//
//  Start 			: 2007.07.13 Friday
//
///////////////////////////////////////////////////////////////////////////

// must be added below codeing to origin 16F877A.H file
#device PIC16F877A

#device *=8 ICD=TRUE
#device ADC=8
#use delay(clock=8000000)
#fuses WDT,HS,PUT, NOPROTECT,LVP, NOCPD,BROWNOUT
#list

#include	<16F877A.h>
#include 	<string.h>
#include	<define.h>
#include	<ctype.h>

#include	<stddef.h>
#include 	"sci.h"
#include 	"ewdo21.h"

#include	"global.h"
#include	"extern.h"
#include	"Module.h"

#include	"LCD.C"
#include 	"sci.c"
#include 	"sub.c"
#include 	"KeyProc.c"


//#use fast_io(C)		// SPI동작을 위하여는 fast_io를 사용하면 안된다. 2005.02.21

#SEPARATE
void PowerOnSetProc();
/*		
		if( secWatchDog > 60 ){
			secWatchDog = 0;
			delay_ms(100); 
			sci_rx_msg_start = sci_rx_msg_end = 0;
			LCD_Initialization();				
			machine_state = STATE_MONITOR_MODE;
			delay_ms(100); 
		}
		
		if(machine_state != STATE_EDIT_MODE  && machine_state != STATE_TIME_MODE)
			LCD_Cmd(CURSOR_OFF);

*/
#SEPARATE
void main()
{

	PowerOnSetProc();
	
	LCD_Cmd(DISPLAY_CURSE_BLINK_ON);
	machine_state = STATE_MONITOR_MODE;

	while(1){

		if( secWatchDog > 60 ){
			secWatchDog = 0;
			delay_ms(100); 
			sci_rx_msg_start = sci_rx_msg_end = 0;
			LCD_Initialization();				
			machine_state = STATE_MONITOR_MODE;
			delay_ms(100); 
		}
		

		if	   ( machine_state == STATE_SET_MODE ) SelectMenuPage1();			// 모드 선택
		else if( machine_state == STATE_SET_MODE2 ) SelectMenuPage2();			// 모드 선택
		else if( machine_state == STATE_EDIT_MODE) EditCodeDataProc();			// 사용자 에디터 모드
		else if( machine_state == STATE_TRIP_MODE) TripCodeDataProc();			// Trip 모드 (저장 데이터)
		else if( machine_state == STATE_RESET_MODE) ResetCodeDataProc();		// Reset 모드
		else if( machine_state == STATE_TIME_MODE) TimeDataSetProc();			// 시간 셋팅 모드
		// else if( machine_state == STATE_ERROR_MODE)	ErrorCodeDataProc();		// TRIP ERROR 모드
		else if( machine_state == RECORD_CLEAR_MODE) RecordClearProc();			// Trip 이력 모두 삭제
		else if( machine_state == SYSTEM_INIT_MODE) SystemInitProc();			// EEPROM DATA 초기화
		else if( machine_state == CHECKSUM_MODE) CheckSumErrorProc();			// Checksum 복구모드
		else if( machine_state == STATE_POSITION_MODE) PositionTestProc();		// TEST
		else {   machine_state = STATE_MONITOR_MODE; monitor_converter();}
	}
}

#SEPARATE
void PowerOnSetProc()
{		 	
	port_b_pullups(TRUE);	output_b(0xff); output_c(0xff);		
	
	set_tris_A(0b00000011);	set_tris_B(0b01111111);

	set_tris_D(0b00000000);	set_tris_E(0b00000000);
	
	set_tris_C(0b10010000);
	
	setup_adc_ports(NO_ANALOGS);
	setup_adc(ADC_OFF);

	setup_comparator(NC_NC_NC_NC);
	setup_vref(FALSE);
	setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);

	setup_timer_2(T2_DIV_BY_4,250,2);		 // 8,000,000 / (4 * 8 * (249 +1)) = 1,000 = 1/1000 sec
	set_timer2(0);
	enable_interrupts(INT_TIMER2);
	
	// LCD 초기화 하기 전에 대기 없으면 이상한 현상이 생김  
	delay_ms(100); 

	LCD_Initialization();				

	setup_psp(PSP_DISABLED);	
	delay_ms(250);
	SerialPortSetup();	

	LCD_Clear();
	enable_interrupts(INT_RDA);	
	enable_interrupts(GLOBAL);	

             //"01234567890123456789"
	strcpy(st, "DIGITAL OPERAT      "); PrintLCD(0,0,st);
	strcpy(st, "[EwDo-21] v2.60     "); PrintLCD(1,0,st);
	strcpy(st, "EunWho Power Electic"); PrintLCD(2,0,st);
	strcpy(st, "TEL 82-51-262-7532  "); PrintLCD(3,0,st);
	delay_ms(3250);
	delay_ms(3250);
}

#INT_TIMER2
void Timer2_Interrupt()
{
	static long watchdog=0;
	#asm
		clrwdt				// watch dog timer reset.
	#endasm

	
	gulRtsCount ++;			// 1 msec count 
	watchdog ++;
	if(watchdog  > 1000){
		watchdog = 0;
		secWatchDog++;
	}
 
#if TEST_MODE
	if( glRtsCount % 2 ) 	output_high(TEST_PIN);	// debug
	else					output_low(TEST_PIN);	//
#endif
}
