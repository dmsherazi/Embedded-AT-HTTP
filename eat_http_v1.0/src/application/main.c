/*


*/

#include "global_var.h"
#include "global_var.c"
#include "modem.h"
#include "modem.c"
#include "timer.h"
#include "timer.c"
#include "filesystem.c"
#include "filesystem.h"
#include "sms.c"
#include "sms.h"
#include "ota.h"
#include "ota.c"
#include "uart.h"
#include "uart.c"

#include "eat_clib_define.h" //only in main.c

/********************************************************************
* Types
********************************************************************/
typedef void (*app_user_func)(void*);

/********************************************************************
* Local Variables:  STATIC
********************************************************************/
EatUartConfig_st uart_config;
/********************************************************************
* External Functions declaration
********************************************************************/
extern void APP_InitRegions(void);

/********************************************************************
* Local Function declaration
********************************************************************/
void app_main(void *data);
void app_func_ext1(void *data);
//void app_user1(void *data);
/********************************************************************
* Local Function
********************************************************************/
#pragma arm section rodata = "APP_CFG"
APP_ENTRY_FLAG
#pragma arm section rodata

#pragma arm section rodata="APPENTRY"
const EatEntry_st AppEntry =
{
	app_main,
	app_func_ext1,
	(app_user_func)EAT_NULL,//app_user1,
	(app_user_func)EAT_NULL,//app_user2,
	(app_user_func)EAT_NULL,//app_user3,
	(app_user_func)EAT_NULL,//app_user4,
	(app_user_func)EAT_NULL,//app_user5,
	(app_user_func)EAT_NULL,//app_user6,
	(app_user_func)EAT_NULL,//app_user7,
	(app_user_func)EAT_NULL,//app_user8,
	EAT_NULL,
	EAT_NULL,
	EAT_NULL,
	EAT_NULL,
	EAT_NULL,
	EAT_NULL
};
#pragma arm section rodata

void app_func_ext1(void *data)
{
	//Init app RAM
	APP_InitRegions();
	APP_init_clib();
	uart_config.baud = EAT_UART_BAUD_115200;
	uart_config.dataBits = EAT_UART_DATA_BITS_8;
	uart_config.parity = EAT_UART_PARITY_NONE;
	uart_config.stopBits = EAT_UART_STOP_BITS_1;

	eat_uart_set_at_port(EAT_UART_NULL);
	eat_uart_set_debug(EAT_UART_NULL);
	
	
	
	//// Configure Inputs
	//eat_pin_set_mode(LOW_SENSE_2, EAT_PIN_MODE_GPIO);
	//eat_gpio_set_pull(LOW_SENSE_2, EAT_TRUE, EAT_GPIO_LEVEL_HIGH);
	//eat_gpio_setup(LOW_SENSE_2, EAT_GPIO_DIR_INPUT, EAT_GPIO_LEVEL_HIGH);
	
	//// Configure Outputs
	//eat_pin_set_mode(OUTPUT_1, EAT_PIN_MODE_GPIO);
	//eat_gpio_setup(OUTPUT_1, EAT_GPIO_DIR_OUTPUT, EAT_GPIO_LEVEL_LOW);
	
	//UART2
	eat_pin_set_mode(EAT_PIN7_CTS,EAT_PIN_MODE_UART);		// UART2 RXD
	eat_pin_set_mode(EAT_PIN8_RTS,EAT_PIN_MODE_UART);		// UART2 TXD
	
	//UART1
	eat_pin_set_mode(EAT_PIN9_TXD,EAT_PIN_MODE_UART);		// UART1 TXD
	eat_pin_set_mode(EAT_PIN10_RXD,EAT_PIN_MODE_UART);		// UART1 RXD

}

void sys_init()
{
	eat_bool debug_f;
	debug_f = eat_uart_open(DEBUG_UART);
	eat_uart_set_config(DEBUG_UART, &uart_config);
	if (debug_f == 0)
	{
		eat_reset_module();
	}
	eat_debug("\n\n*****SYS INIT*****\n\n");
	eat_sleep(100);
	
	eat_modem_read(g_modemRxBuff,35);
	eat_debug((char*)&g_modemRxBuff);
	eat_sleep(2000);
	eat_modem_read(g_modemRxBuff,25);
	eat_debug((char*)&g_modemRxBuff);
	
	eat_timer_start(MODEM_TIMER,5000);
}

// _______________________________ app main thread _________________________________________
void app_main(void *data)
{
	eat_sleep(5000);
	sys_init();
		
	while (EAT_TRUE)
	{
		eat_get_event(&event);
		switch(event.event)
		{
			case EAT_EVENT_UART_READY_RD:
			{
				
			}
			break;
			
			case EAT_EVENT_UART_SEND_COMPLETE :
			{
				
			}
			break;
			
			case EAT_EVENT_TIMER:
			{
				if(event.data.timer.timer_id == MODEM_TIMER)
				{
					eat_timer_start(MODEM_TIMER,200);
					if(g_modemReadStatus == 2)
					{
						validate_modem_response();
					}
					else if(g_modemReadStatus == 1)
					{
						read_from_modem();
					}
					else
					{
						write_to_modem();
					}
				}	
			}
			break;
			
			case EAT_EVENT_MDM_RI:
			{
				
			}break;
			
			default:
			{
				
			}
			break;
		}
			
	}
}

