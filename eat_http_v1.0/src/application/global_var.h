#ifndef GLOBAL_VAR_H_
#define GLOBAL_VAR_H_

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "eat_audio.h"
#include "eat_flash.h"
#include "eat_fs.h"
#include "eat_fs_errcode.h"
#include "eat_fs_type.h"
#include "eat_inputmethod.h"
#include "eat_interface.h"
#include "eat_mem.h"
#include "eat_modem.h"
#include "eat_nvram.h"
#include "eat_other.h"
#include "eat_periphery.h"
#include "eat_sim.h"
#include "eat_sms.h"
#include "eat_socket.h"
#include "eat_timer.h"
#include "eat_type.h"
#include "eat_uart.h"

EatEvent_st event;

#define MODEM_TIMER		EAT_TIMER_16

// Hardware related
#define APP_STORAGE_OFFSET      0x00025800		//100KB  0x00019000       150KB 0x00025800
#define APP_UPDATE_BUFF_SIZE	1024
#define EAT_UART_RX_BUF_LEN_MAX 512
#define GSM_BUF_MAX_LEN			200
#define MODEM_BUF_MAX_LEN		100
#define DEBUG_STRING_MAX_LEN	100

// UART related
#define DEBUG_UART  EAT_UART_1

extern volatile u32 g_atCommandIndex;

extern volatile char g_apn[15];
extern volatile char g_modemRxBuff[2048];
extern volatile char g_modemReadStatus;

typedef enum 
{
	echoOff			=0,
	at				=1,
	cpinReady		=2,
	networkOK		=3,
	gprsRegistered	=4,
	signalStrength	=5	
}_modem_state;

typedef struct  
{
	_modem_state modemState;
	u8 *atCommand;
	unsigned short commandLength;
	const u8 *atCommandResponse;
	u32 minResponseLength;
	u32 maxResponseLength;
	u32 msTimeOut;
	unsigned short cmdFailCnt;
	u32 atDelayBwCmnds;
}_at_command_set;

const _at_command_set atCommandSet[] = {
	{0,"ATE0\r",5,"OK",2,20,2000,15,2000},
	{1,"AT\r",3,"OK",2,5,2000,5,1000},
	{2,"AT+CPIN?\r",9,"+CPIN:",7,25,3000,10,1000},
	{3,"AT+CREG?\r",9,"+CREG: ",7,15,3000,10,1000},
	{4,"AT+CGREG?\r",10,"+CGREG: ",7,16,3000,10,1000},
	{5,"AT+CSQ\r",8,"+CSQ:",6,16,3000,10,1000},
	{6,g_apn,8,"+CSQ:",6,16,3000,10,1000},
};

#define ATCSI	atCommandSet[g_atCommandIndex]				//AT Command Set With Index

enum enum_sms_read
{
	read_webstart,
	read_dns,
	read_flash_erase,
	read_bal,
	read_gprs_status,
	read_sys_status,
	read_factory_reset,
	read_pass_word,
	read_version,
	read_get_gps,
	read_apn_user_pwd,
	read_sleep_data_limit,
	read_change_config,
	read_arm,
	read_disarm,
	read_sleep_on,
	read_sleep_off,
	read_debug_on,
	read_debug_off,
	read_operator_name,
	read_accel_error,
	read_masteronly_serverip_portno_change,
	read_reprogram,
	read_accelerometer,
	read_sri,
	read_cell_id,
	read_debug_file,
	read_none
};

typedef struct
{
	char *string;
	u8 code;
}lookuptable;

const lookuptable tab[]= {
	{"WEBSTART",read_webstart},
	{"BAL",read_bal},
	{"FR",read_factory_reset},
	{"PW",read_pass_word},
	{"FE",read_flash_erase},
	{"DNS",read_dns},
	{"GPRSSTATUS", read_gprs_status},
	{"SYSSTATUS", read_sys_status},
	{"CCID?",read_cell_id},
	{"VERSION",read_version},
	{"GETGPS",read_get_gps},
	{"#CONFIG",read_apn_user_pwd},
	{"SDL",read_sleep_data_limit},
	{"CO?",read_operator_name},
	{"#CC",read_change_config},
	{"ARM",read_arm},
	{"DISARM",read_disarm},
	{"SLEEPON",read_sleep_on},
	{"SLEEPOFF",read_sleep_off},
	{"DEBUGON",read_debug_on},
	{"DEBUGOFF",read_debug_off},	
	{"ERROR",read_accel_error},
	{"#SERVERCHANGE",read_masteronly_serverip_portno_change},
	{"GSENSE",read_accelerometer},
	{"#REPROGRAM",read_reprogram},
	{"SRI",read_sri},
	{"DEBUGFILE",read_debug_file},
};

/********************************	Flags as bitfields	******************************************************************************/
typedef struct _flags
{
	volatile u8 g_systemStarted_F		:1;
	volatile u8 g_modemRead_F			:1;
	volatile u8 g_isCommandCrucial_F	:1;
}flags;

extern volatile flags f;

#endif /* GLOBAL_VAR_H_ */

