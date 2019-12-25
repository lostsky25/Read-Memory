#ifndef _TBV_H
#define _TBV_H

#include "stdint.h"
#include "../debug_lib/debug.h"

#define IMS_DATA_SZ 0x800

//#define _CURRENT_TIME get_tbv_time();
//#define _BEGIN_TIME(X) set_tbv_time(X);

//Регистр счетчика
uint64_t get_tbv_time(void);
uint64_t set_tbv_time(uint64_t data);

#endif
