/*
 * uart.c
 *
 * Created: 05-Apr-15 9:45:49 PM
 *  Author: H
 */ 

#include "uart.h"

void eat_debug(char *buff)
{
	eat_uart_write(DEBUG_UART,(const unsigned char*)buff,strlen(buff));
}


