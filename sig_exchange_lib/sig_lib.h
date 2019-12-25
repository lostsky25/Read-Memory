#ifndef SIG_LIB_H_
#define SIG_LIB_H_

#include "open_sdk.h"
#include "pm_module.h"
#include "../debug_lib/err_lib.h"
#include "../debug_lib/debug.h"

//PM_STATUS_INI
struct Init{
	SIGSELECT sig_no;
};

//PM_STATUS_READY
struct Ready{
	SIGSELECT sig_no;
};

//PM_STATUS_START
struct Start{
	SIGSELECT sig_no;
};

//PM_STATUS_SUCCESS
struct Success{
	SIGSELECT sig_no;
};

//PM_STATUS_END
struct End{
	SIGSELECT sig_no;
};

typedef void (*fns_ptr)(SIGSELECT);

//Имя принемаемого модуля и передаваемые данные
errcode_t send_sig_module(const char*, pm_signals_t);

//Имя принемаемого модуля
errcode_t send_sig_module_em(const char*, pm_signals_t);

//Имя прослушиваемого модуля, указатель на обработчик и таймаут квитанции
SIGSELECT rec_sig_module(const char*, OSTIME);

//Имя прослушиваемого модуля и таймаут квитанции (без обработчика)
SIGSELECT rec_w_sig_module(const char*, fns_ptr, OSTIME);

#endif /* SIG_LIB_H_ */
