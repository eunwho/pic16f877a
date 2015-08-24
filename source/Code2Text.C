/////////////////////////////////////////////////////////////////////////////////
//
//  date : 2007.06.30
//    기존의 어드레스와 연결하기 위한 작업 
//    가능한 한 간단하게 끝을 내는 방법으로 처리를 한다. 
//    
/////////////////////////////////////////////////////////////////////////////////


// Data = 000.0 으로 입력된 스트링을 int 로 변경을 한다. 

// A11~A14 아날로그 지령 입력 설정 		
#define ADDR_ANA_IN_OFFSET				11		// 1
#define ADDR_ANA_IN_GAIN				12		// 2
#define ADDR_ANA_CMD_FREQ_L				13		// 3
#define ADDR_ANA_CMD_FREQ_U				14		// 4
// A21~A23 아날로그 모니터 CH1 설정 		
#define ADDR_ANA_MONIT_CH1_PTR			24		// 5
#define ADDR_ANA_MONIT_CH1_OFFSET		25		// 6 
#define ADDR_ANA_MONIT_CH1_GAIN			26		// 7
// A31~A33 아날로그 모니터 CH2 설정 		
#define ADDR_ANA_MONIT_CH2_PTR			31		// 8
#define ADDR_ANA_MONIT_CH2_OFFSET		32		// 9
#define ADDR_ANA_MONIT_CH2_GAIN			33		// 10
// A41~A43 D/A CH1 설정  		
#define ADDR_DA_CH1_PTR					41		// 11
#define ADDR_DA_CH1_OFFSET				42		// 12
#define ADDR_DA_CH1_GAIN				43		// 13
// A51~A53 D/A CH2 설정  		
#define ADDR_DA_CH2_PTR					51		// 14
#define ADDR_DA_CH2_OFFSET				52		// 15
#define ADDR_DA_CH2_GAIN				53		// 16
// A61~A63 D/A CH3 설정 				 		
#define ADDR_DA_CH3_PTR					61		// 17
#define ADDR_DA_CH3_OFFSET				62		// 18
#define ADDR_DA_CH3_GAIN				63		// 19
// A71~A73 D/A CH4 설정  		
#define ADDR_DA_CH4_PTR					71		// 20
#define ADDR_DA_CH4_OFFSET				72		// 21
#define ADDR_DA_CH4_GAIN				73		// 22

#SEPARATE
void GetGroupAText(int Code, char * str)
{
	char st[21];
	st[20] = 0; 

	switch(Code)
	{
// A11~A14 아날로그 지령 입력 설정 		
		case ADDR_ANA_IN_OFFSET			: strcpy(st,"ANA CMD Offset")		; break;	
		case ADDR_ANA_IN_GAIN			: strcpy(st,"ANA CMD Gain")			; break;
		case ADDR_ANA_CMD_FREQ_L		: strcpy(st,"ANA CMD Freq MIN")		; break;	
		case ADDR_ANA_CMD_FREQ_U		: strcpy(st,"ANA CMD FREQ MAXC")	; break;	
// A21~A23 아날로그 모니터 CH1 설정 		
		case ADDR_ANA_MONIT_CH1_PTR		: strcpy(st,"ANA MONIT CH1 PTR")	; break;	
		case ADDR_ANA_MONIT_CH1_OFFSET	: strcpy(st,"ANA MONIT CH1 OFFSET")	; break;	
		case ADDR_ANA_MONIT_CH1_GAIN	: strcpy(st,"ANA MONIT CH1 GAIN")	; break;	
// A31~A33 아날로그 모니터 CH2 설정 		
		case ADDR_ANA_MONIT_CH2_PTR		: strcpy(st,"ANA MONIT CH2 PTR")	; break;	
		case ADDR_ANA_MONIT_CH2_OFFSET	: strcpy(st,"ANA MONIT CH2 OFFSET")	; break;	
		case ADDR_ANA_MONIT_CH2_GAIN	: strcpy(st,"ANA MONIT CH2 GAIN")	; break;	
// A41~A43 D/A CH1 설정  		
		case ADDR_DA_CH1_PTR			: strcpy(st,"DA CH1 PTR")			; break;	
		case ADDR_DA_CH1_OFFSET			: strcpy(st,"DA CH1 OFFSET")		; break;	
		case ADDR_DA_CH1_GAIN			: strcpy(st,"DA CH1 GAIN")			; break;	
// A51~A53 D/A CH2 설정  		
		case ADDR_DA_CH2_PTR			: strcpy(st,"DA CH2 PTR")			; break;	
		case ADDR_DA_CH2_OFFSET			: strcpy(st,"DA CH2 OFFSET")		; break;	
		case ADDR_DA_CH2_GAIN			: strcpy(st,"DA CH2 GAIN")			; break;
// A61~A63 D/A CH3 설정  		
		case ADDR_DA_CH3_PTR			: strcpy(st,"DA CH3 PTR")			; break;	
		case ADDR_DA_CH3_OFFSET			: strcpy(st,"DA CH3 OFFSET")		; break;	
		case ADDR_DA_CH3_GAIN			: strcpy(st,"DA CH3 GAIN")			; break;
// A71~A73 D/A CH4 설정  		
		case ADDR_DA_CH4_PTR			: strcpy(st,"DA CH4 PTR")			; break;	
		case ADDR_DA_CH4_OFFSET			: strcpy(st,"DA CH4 OFFSET")		; break;	
		case ADDR_DA_CH4_GAIN			: strcpy(st,"DA CH4 GAIN")			; break;
	default 								: strcpy(st,"Invalid Address")		; break;
	}
	strcopy(str,st);
}


//=============================================================================
// 
//  브레이크 동작과 릴레이 동작 옵션 
//  B11~
//
//=============================================================================

// B11~ B13디지털 I/O 설정 	
#define ADDR_BINARY_IN				11	// 1 New Code 1
#define ADDR_RELAY_ON_Hz			12	// 2 New Code 2
#define ADDR_RELAY_OFF_Hz			13	// 3 New Code 2

// B11~B16 브레이크 동작 설정 				
#define ADDR_BRAKE_ON_Hz			21	// 4 	ref -> Hz로 수정 
#define ADDR_BRAKE_OFF_Hz			22	// 5 	ref--> Hz로 수정 
#define ADDR_BRAKE_ON_DELAY_TIME	23	// 6	ref--> Hz로 수정 
#define ADDR_BRAKE_OFF_DELAY_TIME	24	// 7	ref--> Hz로 수정 
#define ADDR_BRAKE_TORQ_BOOST_TIME	25	// 8	ref--> Hz로 수정 
#define ADDR_BRAKE_ZERO_HOLD_TIME	26	// 8	ref--> Hz로 수정 

#SEPARATE
void GetGroupBText(int Code,char *str)
{
	char st[21];
	st[20]=0;
	
	switch(Code){
// B11~ B13디지털 I/O 설정 	
	case ADDR_BINARY_IN					: strcpy(st,"DIO Input Binary ?")	; break;
	case ADDR_RELAY_ON_Hz				: strcpy(st,"Relay On Hz")			; break;
	case ADDR_RELAY_OFF_Hz				: strcpy(st,"Relay Off Hz")			; break;

// B11~B16 브레이크 동작 설정 				
	case ADDR_BRAKE_ON_Hz				: strcpy(st,"Brake On Hz")			; break;
	case ADDR_BRAKE_OFF_Hz				: strcpy(st,"Brake Off Hz")			; break;
	case ADDR_BRAKE_ON_DELAY_TIME		: strcpy(st,"Brake On Delay sec")	; break;
	case ADDR_BRAKE_OFF_DELAY_TIME		: strcpy(st,"Brake Off Delay sec")	; break;
	case ADDR_BRAKE_TORQ_BOOST_TIME		: strcpy(st,"Brake Torq Boost sec")	; break;
	case ADDR_BRAKE_ZERO_HOLD_TIME		: strcpy(st,"Brake Zero Hold sec")	; break;
	default 							: strcpy(st,"Invalid Address")		; break;
	}
	strcopy(str,st);
}

//=============================================================================
// 
//  속도 지령과 제어 방법  
//  C11~
//
//=============================================================================

// C11~ C13 속도지령 방법/ 제어방법 / 방향 전환 	
#define ADDR_CMD_INPUT_SET			11 	// 1 New Code  Add prog not used in C32
#define ADDR_CTRL_TYPE_SET			12	// 2 New Code 2 수정 
#define ADDR_CHANGE_DIRECTION		13	// 3 New Code 2 수정 
	
// C21~C24 가감속 시간 설정  				
#define ADDR_ACCEL1_TIME			21	// 4 	 
#define ADDR_DECEL1_TIME			22	// 5 
#define ADDR_ACCEL2_TIME			23	// 6 New 수정 
#define ADDR_DECEL2_TIME			24	// 7 New 수정 

// C31~C38 다단 속도 설정  				
#define ADDR_JOG_SPEED				31	// 8 수정  크레인 모드인 경우에는 가속을 최대로 하여 토크 모드로한다.  
#define ADDR_DIN_SPEED2				32	// 9  
#define ADDR_DIN_SPEED3				33	// 10  
#define ADDR_DIN_SPEED4				34	// 11
#define ADDR_DIN_SPEED5				35	// 12
#define ADDR_DIN_SPEED6				36	// 13 수정 
#define ADDR_DIN_SPEED7				37	// 14 수정 
#define ADDR_DIN_SPEED8				38	// 15 수정 

#SEPARATE
void GetGroupCText(int Code, char * str)
{
	char st[21];
	st[20]=0;
	
	switch(Code){
// C11~ C13 속도지령 방법 외 	
	case ADDR_CMD_INPUT_SET				: strcpy(st,"Select CMD In Type")	; break;
	case ADDR_CTRL_TYPE_SET				: strcpy(st,"Select CTRL Type")		; break;
	case ADDR_CHANGE_DIRECTION			: strcpy(st,"Direction Change")		; break;
// C21~C24 가감속 시간 설정  				
	case ADDR_ACCEL1_TIME				: strcpy(st,"Accel Ramp1 sec")		; break;
	case ADDR_DECEL1_TIME				: strcpy(st,"Decel Ramp1 sec")		; break;
	case ADDR_ACCEL2_TIME				: strcpy(st,"Accel Ramp2 sec")		; break;
	case ADDR_DECEL2_TIME				: strcpy(st,"Decel Ramp2 sec")		; break;

// C31~C38 다단 속도 설정  				
	case ADDR_JOG_SPEED					: strcpy(st,"Jog Speed Hz")			; break;
	case ADDR_DIN_SPEED2				: strcpy(st,"DIN Speed2 Hz")		; break;
	case ADDR_DIN_SPEED3				: strcpy(st,"DIN Speed3 Hz")		; break;
	case ADDR_DIN_SPEED4				: strcpy(st,"DIN Speed4 Hz")		; break;
	case ADDR_DIN_SPEED5				: strcpy(st,"DIN Speed5 Hz")		; break;
	case ADDR_DIN_SPEED6				: strcpy(st,"DIN Speed6 Hz")		; break;
	case ADDR_DIN_SPEED7				: strcpy(st,"DIN Speed7 Hz")		; break;
	case ADDR_DIN_SPEED8				: strcpy(st,"DIN Speed8 Hz")		; break;
	default 							: strcpy(st,"Invalid Address")		; break;
	}
	strcopy(str,st);
}

//=============================================================================
// 
// D11~ D15 보호 레벨 설정  	
//
//=============================================================================

// D11~ D15 보호 레벨 설정  	
#define ADDR_OVER_CURRENT_LEVEL		11	// 1 RMS 값으로 입력하는 것으로 수정 
#define ADDR_OVER_VOLTAGE_LEVEL		12	// 2 DC link Voltage OV1은 자동으로 계산 할 것   
#define ADDR_UNDER_VOLTAGE_LEVEL	13	// 3 수정 
#define ADDR_OVER_SPEED_LEVEL		14	// 4 수정 
#define ADDR_ETHERMAL_LEVEL			15	// 5 New 수정 
	
// D31~D32  				
#define ADDR_ENCODER_PULSE			21	// 9 
#define ADDR_485_ADDR				22	// 10  

#SEPARATE
void GetGroupDText(int Code,char * str)
{
	char st[21];
	st[20]=0;
	
	switch(Code){
// D11~ D15 보호 레벨 설정  	
	case ADDR_OVER_CURRENT_LEVEL		: strcpy(st,"Over I Level Amp")		; break;
	case ADDR_OVER_VOLTAGE_LEVEL		: strcpy(st,"Over V Level V")		; break;
	case ADDR_UNDER_VOLTAGE_LEVEL		: strcpy(st,"Under v level V")		; break;
	case ADDR_OVER_SPEED_LEVEL			: strcpy(st,"Over Speed Level RPM")	; break;
	case ADDR_ETHERMAL_LEVEL			: strcpy(st,"E Thermal Level %")	; break;
	
// D21~D22 Encoder Pulse Count & 485 Address set    				
	case ADDR_ENCODER_PULSE				: strcpy(st,"Encoder Pulse/Rot")	; break;
	case ADDR_485_ADDR					: strcpy(st,"RS-485 Address")		; break;
	default 							: strcpy(st,"Invalid Address")		; break;
	}
	strcopy(str,st);
}

//=======================================================================
//
//  ACIM Parameter Estimation & Sensorless Vector Control
//
//
//=======================================================================


// E11~E17 전동기 정격 입력   	
#define ADDR_MOTOR_RATE_POWER				11	
#define ADDR_MOTOR_RATE_VOLT				12	
#define ADDR_MOTOR_RATE_CURRENT				13	
#define ADDR_MOTOR_RATE_Hz					14
#define ADDR_MOTOR_RATE_RPM					15
#define ADDR_MOTOR_POLE						16
#define ADDR_MOTOR_EFFIENCY 				17
	
// E21 오토 튜닝 시작    				
#define ADDR_TUNING_START 					21
// E31~D36 전동기 상수   				
#define ADDR_MOTOR_RS 						31
#define ADDR_MOTOR_Rr 						32
#define ADDR_MOTOR_Ls_mH 					33
#define ADDR_MOTOR_Lr_mH 					34
#define ADDR_MOTOR_Lm_mH 					35
#define ADDR_MOTOR_Jm						36

// E41~E45 벡터 제어 상수 
#define ADDR_SLIP_COMP 						41
#define ADDR_GammaLambda 					42
#define ADDR_Max_Delta_Lambda 				43
#define ADDR_GammaTheta_M 					45
#define ADDR_GammaTheta_R 					46
// E51~E55 벡터 제어 상수 
#define ADDR_Default_wr_Filter_Pole 		51
#define ADDR_GammaLambda_R_Constant 		52
#define ADDR_Max_DeltaTheta 				53	
#define ADDR_Delta_wr_FilterPoleCoeff_L 	54	
#define ADDR_Delta_wr_FilterPoleCoeff_U 	55	
// E61~E66
#define ADDR_TUNNING_L_Hz 					61
#define ADDR_TUNNING_L_TIME 				62
#define ADDR_TUNNING_L_CURRENT 				63
#define ADDR_TUNNING_Rs_AMP					65 
#define ADDR_TUNNING_Rs_TIME 				66
#define ADDR_TUNNING_DEAD_BAND_GAIN 		67
// E71~E76
#define ADDR_TUNNING_Ls_Vs_RAMP 			71
#define ADDR_TUNNING_Ls_Hz 					72
#define ADDR_TUNNING_Ls_TIME 				73
#define ADDR_TUNNING_BRAKE_OPEN_TIME 		74
#define ADDR_TUNNING_Jm_Te_Ratio 			75
#define ADDR_TUNNING_Jm_TIME 				76

// E81~E85 센서리스 벡터 제어 속도 제어 상수 
#define ADDR_SL_wr_FilterPole 				81
#define ADDR_SL_wn_wr_Ratio 				82
#define ADDR_SL_MAX_wn_wr 					83
#define ADDR_SL_K_Damp_wr 					84
#define ADDR_SL_wr_DampingRatio 			85

#SEPARATE
void GetGroupEText(int Code, char *str)
{
	char st[21];
	st[20] = 0;

	switch(Code){
// E11~E7 전동기 정격 입력   	
	case ADDR_MOTOR_RATE_POWER				: strcpy(st,"Motor Rated Power")	; break;
	case ADDR_MOTOR_RATE_VOLT				: strcpy(st,"Motor Rated Volt")		; break;
	case ADDR_MOTOR_RATE_CURRENT			: strcpy(st,"Motor Rated Ampere")	; break;
	case ADDR_MOTOR_RATE_Hz					: strcpy(st,"Motor Rated Hz")		; break;
	case ADDR_MOTOR_RATE_RPM				: strcpy(st,"Motor Rated RPM")		; break;
	case ADDR_MOTOR_POLE					: strcpy(st,"Motor Pole")			; break;
	case ADDR_MOTOR_EFFIENCY				: strcpy(st,"Motor Efficieny")		; break;
	
// E21 오토 튜닝 시작    				
	case ADDR_TUNING_START					: strcpy(st,"Tuning Start ? ")		; break;

// E31~D36 전동기 상수   				
	case ADDR_MOTOR_RS						: strcpy(st,"Motor Rs")				; break;
	case ADDR_MOTOR_Rr						: strcpy(st,"Motor Rr")				; break;
	case ADDR_MOTOR_Ls_mH					: strcpy(st,"Motor Ls mH")			; break;
	case ADDR_MOTOR_Lr_mH					: strcpy(st,"Motor Lr mH")			; break;
	case ADDR_MOTOR_Lm_mH					: strcpy(st,"Motor Lm mH")			; break;
	case ADDR_MOTOR_Jm						: strcpy(st,"Motor Jm")				; break;

// E41~E45 벡터 제어 상수 
	case ADDR_SLIP_COMP						: strcpy(st,"Slip Comp Ratio")		; break;
	case ADDR_GammaLambda					: strcpy(st,"Gamma Lambda")			; break;
	case ADDR_Max_Delta_Lambda				: strcpy(st,"Max Delta GamaLamda")  ; break;
	case ADDR_GammaTheta_M					: strcpy(st,"Motoring GammaTheta")	; break;
	case ADDR_GammaTheta_R					: strcpy(st,"Generat'n GammaTheta")	; break;

// E51~E55 벡터 제어 상수 
	case ADDR_Default_wr_Filter_Pole		: strcpy(st,"Init wr filter Pole")	;
	case ADDR_GammaLambda_R_Constant		: strcpy(st,"GammaLambda_R_Cons")	; break;
	case ADDR_Max_DeltaTheta				: strcpy(st,"Max DeltaTheta")		; break;
	case ADDR_Delta_wr_FilterPoleCoeff_L	: strcpy(st,"Delta wr Filt PoleL")  ; break;
	case ADDR_Delta_wr_FilterPoleCoeff_U	: strcpy(st,"Delta wr Filt PoleU")	; break;

// E61~E66 오토 뉴닝 파라메터 1
	case ADDR_TUNNING_L_Hz					: strcpy(st,"AT Freq L_R Hz")		; break;
	case ADDR_TUNNING_L_TIME				: strcpy(st,"AT L-R sec")			; break;
	case ADDR_TUNNING_L_CURRENT				: strcpy(st,"AT L-R Amp %")			; break;
	case ADDR_TUNNING_Rs_AMP				: strcpy(st,"AT Rs Amp %")			; break;
	case ADDR_TUNNING_Rs_TIME				: strcpy(st,"AT Rs sec")			; break;
	case ADDR_TUNNING_DEAD_BAND_GAIN		: strcpy(st,"AT DeadTime Gain")		; break;

// E71~E76 오토 뉴닝 파라메터 2
	case ADDR_TUNNING_Ls_Vs_RAMP			: strcpy(st,"AT Ls Vs Ramp sec")	; break;
	case ADDR_TUNNING_Ls_Hz					: strcpy(st,"AT Freq Ls Hz")		; break;
	case ADDR_TUNNING_Ls_TIME				: strcpy(st,"AT Time Ls sec")		; break;
	case ADDR_TUNNING_BRAKE_OPEN_TIME		: strcpy(st,"AT Brake On sec")		; break;
	case ADDR_TUNNING_Jm_Te_Ratio			: strcpy(st,"AT Jm/Te Ratio %")		; break;
	case ADDR_TUNNING_Jm_TIME				: strcpy(st,"AT Time Jm sec")		; break;

// E81~E85 센서리스 벡터 제어 속도 제어 상수 
	case ADDR_SL_wr_FilterPole				: strcpy(st,"wr Filt Pole Coeff")	; break;
	case ADDR_SL_wn_wr_Ratio				: strcpy(st,"wn wr Ratio")			; break;
	case ADDR_SL_MAX_wn_wr					: strcpy(st,"SL Max wn wr")			; break;
	case ADDR_SL_K_Damp_wr					: strcpy(st,"SL K Damp wr")			; break;
	case ADDR_SL_wr_DampingRatio			: strcpy(st,"SL wr DampnRatio")		; break;
	default 								: strcpy(st,"Invalid Address")		; break;
	}
	strcopy(str,st);
}

//==============================================================
//
// G Group Option 
//    Factory Setting and ETC
//
//==============================================================


// G11~G15 인버터 센서 조정    	
#define ADDR_U_PHASE_SENSOR_ADJUST		11
#define ADDR_V_PHASE_SENSOR_ADJUST		12
#define ADDR_U_PHASE_SENSOR_OFFSET		13
#define ADDR_V_PHASE_SENSOR_OFFSET		14
#define ADDR_VDC_SENSOR					15
#define ADDR_I_MAX_RATIO				16
// G21~G25 IGBT Switching Parameter 
#define ADDR_IGBT_SW_KHz				21
#define ADDR_IGBT_SW_TOP_KHz			22
#define ADDR_IGBT_SW_BASE_FUND_Hz		23
#define ADDR_IGBT_SW_TOP_FUND_Hz		24
#define ADDR_IGBT_SW_DEAD_BAND_uS		25

//G31~G39 Scalar Control                              
#define ADDR_DEAD_BAND_COMP_GAIN		31
#define ADDR_VF_EXCIT_TIME				32
#define ADDR_VF_FLUX_RATIO				33
#define ADDR_VF_TORQ_BOOST_Hz			34
#define ADDR_VF_TORQ_BOOST_Vs			35
#define ADDR_VF_RS_COMP_RATIO			36
#define ADDR_VF_IR_COMP_FILT_POLE		37
#define ADDR_VF_SLIP_COMP_FILT_POLE		38
#define ADDR_VF_VF_RS					39

// Inverter Test Code 인버터 성능 검사 기능 
#define ADDR_REF_POSI_TIME				41
#define ADDR_REF_ZERO_TIME				42
#define ADDR_REF_NEGA_TIME				43

//대차 연동제어 기능 
#define ADDR_TORQ_Limit_wr_Filter_Pole  51
#define ADDR_Trq_Limit_Gain				52
#define ADDR_TorqueLimitCoeff			53
#define ADDR_VF_ExcitationCurrentCoeff	54
#define ADDR_VF_CurLimitCoeff			55
#define ADDR_Rev_SlipFreq_ref			56


#SEPARATE
void GetGroupGText(int Code, char *str)
{
	char st[21];
	st[20] = 0;
	 
/*
// G11~G15 인버터 센서 조정    	
	if 	   (Code == ADDR_U_PHASE_SENSOR_ADJUST) 	strcpy(st,"U Phase Amp/V");
	else if(Code == ADDR_V_PHASE_SENSOR_ADJUST)		strcpy(st,"V Phase Amp/V");
	else if(Code == ADDR_U_PHASE_SENSOR_OFFSET)		strcpy(st,"U Phase Amp Offset");
	else if(Code == ADDR_V_PHASE_SENSOR_OFFSET)		strcpy(st,"V Phase Amp Offset");
	else if(Code == ADDR_VDC_SENSOR)				strcpy(st,"Vdc Per Volt");
	else if(Code == ADDR_I_MAX_RATIO)				strcpy(st,"Amp Max Ratio");

// G21~G25 IGBT Switching Parameter    	
	else if(Code == ADDR_IGBT_SW_KHz)				strcpy(st,"IGBT PWM Freq kHz");
	else if(Code == ADDR_IGBT_SW_TOP_KHz)			strcpy(st,"Max PWM Freq kHz");
	else if(Code == ADDR_IGBT_SW_BASE_FUND_Hz)		strcpy(st,"Base Fund Freq Hz");
	else if(Code == ADDR_IGBT_SW_TOP_FUND_Hz)		strcpy(st,"Top Fund Freq Hz");
	else if(Code == ADDR_IGBT_SW_DEAD_BAND_uS)		strcpy(st,"IGBT Dead Band usec");

//G31~G39 Scalar Control                              
	else if(Code == ADDR_DEAD_BAND_COMP_GAIN)		strcpy(st,"VF Dead Time Gain");
	else if(Code == ADDR_VF_EXCIT_TIME)				strcpy(st,"VF ExcitationTime");
	else if(Code == ADDR_VF_FLUX_RATIO)				strcpy(st,"VF Fs Coeff");
	else if(Code == ADDR_VF_TORQ_BOOST_Hz)			strcpy(st,"VF Freq TrqBoost");
	else if(Code == ADDR_VF_TORQ_BOOST_Vs)			strcpy(st,"VF Vs Coeff TrqBoost");
	else if(Code == ADDR_VF_RS_COMP_RATIO)			strcpy(st,"VF Rs ThermalCoeff");
	else if(Code == ADDR_VF_IR_COMP_FILT_POLE)		strcpy(st,"VF IR CompFiltPole");
	else if(Code == ADDR_VF_SLIP_COMP_FILT_POLE)	strcpy(st,"VF SlipCompFiltPole");
	else if(Code == ADDR_VF_VF_RS)					strcpy(st,"VF_Rs");

// Inverter Test Code 인버터 성능 검사 기능 
	else if(Code == ADDR_REF_POSI_TIME)				strcpy(st,"REF POS TIME sec");
	else if(Code == ADDR_REF_ZERO_TIME)				strcpy(st,"REF ZERO TIME sec");
	else if(Code == ADDR_REF_NEGA_TIME)				strcpy(st,"REF NEG TIME sec");
// 대차 연동제어 기능 
	else if(Code == ADDR_TORQ_Limit_wr_Filter_Pole)	strcpy(st,"TrqLimitWrFiltPole");
	else if(Code == ADDR_Trq_Limit_Gain)			strcpy(st,"Trq Limit Gain");
	else if(Code == ADDR_TorqueLimitCoeff)			strcpy(st,"Tor Limit Coeff");
	else if(Code == ADDR_VF_ExcitationCurrentCoeff)	strcpy(st,"VF Excit Amp Coeff");
	else if(Code == ADDR_VF_CurLimitCoeff)			strcpy(st,"VF CurLimitCoeff");
	else if(Code == ADDR_Rev_SlipFreq_ref)			strcpy(st,"Rev Slip Freq Ref");
	else strcpy(st,"Invalid Address");
	}
		
	strcopy(str,st);
*/
}
#SEPARATE	

	
//=======================================================
//
// 송수신 및 데이터 표시의 포맷 
// 						
//  -.000 -0.00 -00.0 -000.
//  0.000 00.00 000.0 0000.
//
//=======================================================

#SEPARATE
signed long slString2Long(char * str, int *Point)
{
	int i;
	char st[5];
	signed long slTemp;
	
	
	st[0] = *str;
	st[1] = *(str +1);
	st[2] = *(str +2);
	st[3] = *(str +3);
	st[4] = *(str +4);

	i =0;

	while((st[i] != '.')&& ( i < 5)) i++;
	
	if(st[0] == '-'){
		switch(i){
		case 1: 
			*point = 3;
			slTemp = (st[2] -'0')*100 +(st[3]-'0')*10+(st[4] -'0');
			slTemp = -slTemp;
		case 2: 
			*point = 2;
			slTemp = (st[1] -'0')*100 +(st[3]-'0')*10+(st[4] -'0');
			slTemp = -slTemp;
			break;		
		case 3:
			*point = 2;
			slTemp = (st[1] -'0')*100 +(st[2]-'0')*10+(st[4] -'0');
			slTemp = -slTemp;
			break;
		case 4:
			*point = 2;
			slTemp = (st[1] -'0')*100 +(st[2]-'0')*10+(st[3] -'0');
			slTemp = -slTemp;
			break;
		default: 
			*point = 255;
			slTemp = -1;
		}
	}
	else{ 
		switch(i){
		case 0:
			*point = 4;			
			slTemp = (signed long)(st[1] -'0')*1000 + (signed long)(st[2]-'0') * 100 + (st[3] -'0')*10 + st[4]-'0';
			break;		
		case 1:
			*point = 3;
			slTemp = (signed long)(st[0] -'0')*1000 + (signed long)(st[2]-'0') * 100 + (st[3] -'0')*10 + st[4]-'0';
			break;		
		case 2: 
			*point = 2;
			slTemp = (signed long)(st[0] -'0')*1000 + (signed long)(st[1]-'0') * 100 + (st[3] -'0')*10 + st[4]-'0';
			break;		
		case 3:
			*point = 1;
			slTemp = (signed long)(st[0] -'0')*1000 + (signed long)(st[1]-'0') * 100 + (st[2] -'0')*10 + st[4]-'0';
			break;
		case 4:
			*point = 0;
			slTemp = (signed long)(st[0] -'0')*1000 + (signed long)(st[1]-'0') * 100 + (st[2] -'0')*10 + st[3]-'0';
			break;
		default: 
			*point = 255;
			slTemp = -1;
		}				
	}
	return slTemp;
}

#SEPARATE
int EpData2String(int Addr, char *str )
{
	int data[4];
	char st[6];

	int point;
	
	int Temp, Temp2, Temp3;
	signed long slTemp;

	point = ReadEeprom(Addr * 3);

	slTemp = (signed long)(ReadEeprom(Addr * 3))*256 + (signed long)(ReadEeprom(Addr * 3));
				
	if(slTemp < 0){
		slTemp = -slTemp;
		st[0] = '-';

		data[0] = slTemp / 1000;
		data[1] = (slTemp % 1000) / 100;
		data[2] = (slTemp % 100)/10;
		data[3] = slTemp % 10 ;
		
		switch(point){
		case 0:	
			st[0] = '-';
			st[1] = data[1];
			st[2] = data[2];
			st[3] = data[3];
			st[4] = '.';
			st[5] = 0;
			break;	
		case 1:	
			st[0] = '-';
			st[1] = data[1];
			st[2] = data[2];
			st[3] = '.';
			st[4] = data[3];
			st[5] = 0;
			break;	
		case 2:	
			st[0] = '-';
			st[1] = data[1];
			st[2] = '.';
			st[3] = data[2];
			st[4] = data[3];
			st[5] = 0;
			break;	
		case 3:	
			st[0] = '-';
			st[1] = '.';
			st[2] = data[1];
			st[3] = data[2];
			st[4] = data[3];
			st[5] = 0;
			break;
		}
	}		
	else{ 		
	
		data[0] = slTemp / 1000;
		data[1] = (slTemp % 1000) / 100;
		data[2] = (slTemp % 100)/10;
		data[3] = slTemp % 10 ;

		switch(point){
		case 0:	
			st[0] = data[0];
			st[1] = data[1];
			st[2] = data[2];
			st[3] = data[3];
			st[4] = '.';
			st[5] = 0;
			break;	
		case 1:	
			st[0] = data[0];
			st[1] = data[1];
			st[2] = data[2];
			st[3] = '.';
			st[4] = data[3];
			st[5] = 0;
			break;	
		case 2:	
			st[0] = data[0];
			st[1] = data[1];
			st[2] = '.';
			st[3] = data[2];
			st[4] = data[3];
			st[5] = 0;
			break;	
		case 3:	
			st[0] = data[0];
			st[1] = '.';
			st[2] = data[1];
			st[3] = data[2];
			st[4] = data[3];
			st[5] = 0;
		case 4:	
			st[0] = '.';
			st[1] = data[0];
			st[2] = data[1];
			st[3] = data[2];
			st[4] = data[3];
			st[5] = 0;
			break;
		}
	}		
	strcopy(str, st);
	return point;
}
		 	
