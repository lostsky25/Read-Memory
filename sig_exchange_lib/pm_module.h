#ifndef _PM_MODULE_H
#define _PM_MODULE_H

#include "stdint.h"

enum PM_SIGNALS{
	PM_STATUS_INI		= 0xFF, 		//Инициализация ПМ
	PM_STATUS_READY		= 0x01, 		//Готовность ПМ
	PM_STATUS_START		= 0x02, 		//Старт ПМ
	PM_STATUS_SUCCESS	= 0x03,  		//ПМ доступен
	PM_STATUS_END 		= 0x04  		//ПМ Завершил работу
};

typedef enum PM_SIGNALS pm_signals_t;

struct PM_INFO{
	const char* name;					//Имя ПМ
	const char* path;					//Путь к *.gz
	const uint16_t timeout_kvit;		//Время ожидания квитанции
	//const unsigned long* compl_filter;  //Фильтр
	//pm_signals_t status;
};

// typedef struct PM_INFO pm_info_t;

#endif
