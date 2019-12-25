#include "sig_lib.h"

/*
 * Набор необходимых сигналов, структуру можно
 * модифицировать при необходимости.
 * */
const SIGSELECT any_sig[] = {
		5,
		PM_STATUS_INI,
		PM_STATUS_READY,
		PM_STATUS_START,
		PM_STATUS_SUCCESS,
		PM_STATUS_END
};

union SIGNAL{
	SIGSELECT sig_no;
	struct Init init;
    struct Ready ready;
	struct Start start;
	struct Success success;
	struct End end;
};

/*
 * Отправка пустого сигнала, то есть без каких-либо данных.
 * Используется для определения\установки состояния ПМ.
 * */
errcode_t send_sig_module_em(const char* pm_name, pm_signals_t signal){
    union SIGNAL *sig;
    PROCESS pm_pid;

    //Получение PID получателя
    if(!hunt(pm_name, 0, &pm_pid, NULL)) return ERR_PID_DATA;

    sig = (union SIGNAL *)alloc(sizeof(union SIGNAL), signal);

    send(&sig, pm_pid);

    return NO_ERROR;
}

/*
 * Отправка сигнала с данными, используестся для передачи сигналов
 * между модулями.
 * */
errcode_t send_sig_module(const char* pm_name, pm_signals_t signal){
    union SIGNAL *sig;
    PROCESS pm_pid;

    //Получение PID получателя
    if(!hunt(pm_name, 0, &pm_pid, NULL)) return ERR_PID_DATA;

    sig = (union SIGNAL *)alloc(sizeof(union SIGNAL), signal);

    send(&sig, pm_pid);

    return NO_ERROR;
}

/*
 * Ожидание сигнала от какого-либо ПМ с заданным таймаутом.
 * */
SIGSELECT rec_sig_module(const char* pm_name, OSTIME kvit_timeout){
    union SIGNAL *sig;
    sig = receive_w_tmo(kvit_timeout, any_sig);

    if(!sig) return (SIGSELECT)ERR_SIG_DATA;

    SIGSELECT sig_num = sig->sig_no;

    free_buf(&sig);

    return sig_num;
}

SIGSELECT rec_w_sig_module(const char* pm_name, fns_ptr init, OSTIME kvit_timeout){
    union SIGNAL *sig;
    sig = receive_w_tmo(kvit_timeout, any_sig);

    if(!sig) return (SIGSELECT)ERR_SIG_DATA;

    init(sig->sig_no);

    SIGSELECT sig_num = sig->sig_no;

    free_buf(&sig);

    return sig_num;
}
