#ifndef MODEM_H_
#define MODEM_H_

#include "global_var.h"
#include "uart.h"

void write_to_modem(void);
void read_from_modem(void);
void validate_modem_response(void);

#endif /* MODEM_H_ */

