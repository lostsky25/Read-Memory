#ifndef _ERR_LIB_H_
#define _ERR_LIB_H_

enum ERROR_e{
	NO_ERROR            = 0,    // Нет ошибки
    ERR_UNDEF           = 1,    // Ошибка неопределенная
    ERR_IMSMEM_RESET    = 2,    // Ошибка сброса защищенной памяти
    ERR_PM_INIT         = 3,    // Ошибка инициализации ПМ
    ERR_KIMC_START      = 4,    // Ошибка установки метки цикла
    ERR_PM_TIMEOUT      = 5,    // Ошибка выполнения ПМ - таймаут
    ERR_PM_NOT_FOUND    = 6,    // Ошибка - процесс ПМ не найден
    ERR_BOOT_START      = 7,    // Ошибка работы менеджера загрузки при старте
    ERR_BOOT_INST       = 8,    // Ошибка работы менеджера загрузки при установке
    ERR_INIT_STATE      = 9,    // Ошибка инициализации признаков состояния
	ERR_WRITE_DATA		= 10,	// Ошибка записи в ячейку памяти
    ERR_READ_DATA		= 11,	// Ошибка чтения ячейки памяти
    ERR_PM_INSTALL      = 12,   // Ошибка установки модуля
    ERR_OSE_MANAGER     = 13,   // Ошибка манеджера операционной системы
    ERR_FD_OPEN         = 14,   // Ошибка в файловом дискрипторе
    ERR_SIG_DATA		= 15,	// Ошибка в структуре SIGSELECT
    ERR_PID_DATA		= 16	// Ошибка получения PID ПМ
};

typedef enum ERROR_e errcode_t;

#endif
