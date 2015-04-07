/*
 * sms.h
 *
 * Created: 09-10-2014 01:02:00
 *  Author: lenovo
 */


#ifndef SMS_H_
#define SMS_H_

#include "global_var.h"
#include "modem.h"
#include "filesystem.h"

void respond_to_sms(char* buff);
void decode_sms(u8 code,char *buff);
void eat_sms_ready_cb(eat_bool result);

#endif /* SMS_H_ */

