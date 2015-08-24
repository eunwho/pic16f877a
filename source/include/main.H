/////////////////////////////////////////////////////////////////////////
//
//	Project Name 		: LCD INPUT for Montrol Inverter
//	Fiele Name		 	: define.h
// 	Discription			: ICD2를 이용한 프로젝트
//	최근 변경 날자 		: 2004.12.23
//  이전 소스일자 		: 2004.12.23
//
///////////////////////////////////////////////////////////////////////////
#include "16F877A.h"
#device *=16 ICD=TRUE
#device adc=8
#use delay(clock=8000000)
#fuses NOWDT,XT, NOPUT, NOPROTECT, LVP, NOCPD, NOWRT, NOBROWNOUT
#list
