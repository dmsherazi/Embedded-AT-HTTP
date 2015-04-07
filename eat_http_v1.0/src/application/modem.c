#include "modem.h"

static unsigned short readLength = 0,cmdFailCnt=0;
static u32 timeout = 0;
static char break_F = 0;
static u32 escTime = 0;

void write_to_modem(void)
{
	static u32 delayCnt = 0;
	delayCnt += 200;
	readLength = 0;
	timeout = 0;
	break_F = 0;
	escTime = 0;
	
	if(delayCnt >= ATCSI.atDelayBwCmnds)
	{
		delayCnt = 0;
		timeout = ATCSI.msTimeOut;	
		escTime = timeout;
		memset(g_modemRxBuff,0x00,2048);
		eat_debug((char*)ATCSI.atCommand);
		eat_modem_write((const unsigned char*)ATCSI.atCommand,ATCSI.commandLength);
		g_modemReadStatus = 1;
	}
}

void read_from_modem(void)
{
	readLength += eat_modem_read((char*)&g_modemRxBuff[readLength],ATCSI.maxResponseLength);
	escTime += 200;
	if(readLength > ATCSI.minResponseLength && break_F == 0)
	{
		break_F = 1;
		escTime = 0;
		timeout = 1500;
	}
	if((escTime > timeout) || (readLength > ATCSI.maxResponseLength))
	{
		g_modemReadStatus = 2;
	}
}

// Handle this function using switch 
void validate_modem_response()
{
	eat_debug(g_modemRxBuff);
	switch(g_atCommandIndex)
	{
		case echoOff:
		{
			if(strstr((const char*)g_modemRxBuff,ATCSI.atCommandResponse))
			{
				cmdFailCnt = 0;
				g_atCommandIndex++;
			}
			else
			{
				cmdFailCnt++;
				if(cmdFailCnt > ATCSI.cmdFailCnt)
				{
					eat_reset_module();
				}
			}
		}
		break;
	}
	g_modemReadStatus = 0;	
	
}


