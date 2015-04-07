/*
* sms.c
*
* Created: 09-10-2014 01:01:29
*  Author: lenovo
*/
#include "sms.h"

void respond_to_sms(char* buff)
{
	int i = 0;
	for(i=0;i<sizeof(tab)/sizeof(tab[0]);i++)
	{
		if(strncmp(buff,(tab[i].string),strlen(tab[i].string)) == 0)
		{
			decode_sms(tab[i].code,buff);
			break;
		}
	}
}

void decode_sms(u8 code,char *buff)
{
	switch(code)
	{
	}
	//eat_debug("Decode complete\n");
}





