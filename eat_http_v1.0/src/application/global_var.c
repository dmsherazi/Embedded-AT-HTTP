#include "global_var.h"

volatile char g_apn[15] = {'A','T','\r','\0'};
volatile u32 g_atCommandIndex = 0;
volatile char g_modemRxBuff[2048] = {0};
volatile char g_modemReadStatus = 0;

volatile flags f;
