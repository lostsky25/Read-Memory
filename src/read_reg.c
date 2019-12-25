#include "stdlib.h"
#include "../sig_exchange_lib/sig_lib.h"
#include "libbru.h"
#include "open_sdk.h"
#include "../tbv_lib/tbv.h"

#define PARTITION_SIZE 8

void signal_init(SIGSELECT);
errcode_t read_drv(PROCESS*, int16_t);

void read_memory();

int32_t main(void){

	//Модуль находится в ожидании
	while(1){
		rec_w_sig_module("main_disp", signal_init, 50);
	}

	stop(current_process());

	return 0;
}

void read_memory(){
	PROCESS drv_pid = 0;

	if(!bru_getPID("regio_bg", &drv_pid)){
		for(int16_t cell = 0; cell <= 16 * 10 + 8; cell += 8){
			read_drv(&drv_pid, cell);
		}
	}
}

void signal_init(SIGSELECT sig_no){
	switch(sig_no){
        case PM_STATUS_INI:{
            print_debug("Пришел сигнал от диспетчера о инициализации в read_reg\r\n");
            send_sig_module_em("main_disp", PM_STATUS_INI);
            break;
        }
        case PM_STATUS_READY:{
            print_debug("Модуль готов к работе\r\n");
            break;
        }
        case PM_STATUS_START:{
        	print_debug("Произошел старт модуля\r\n");
        	read_memory();
        	send_sig_module_em("main_disp", PM_STATUS_END);
        	break;
        }
		case PM_STATUS_SUCCESS:{
			print_debug("Модуль доступен\r\n");
			break;
		}
		case PM_STATUS_END:{
			print_debug("Модуль завершил работу\r\n");
			break;
		}
		default:{
			print_debug("Сигнал не был проиндексирован\r\n");
			break;
		}
    }
}

errcode_t read_drv(PROCESS* pid, int16_t addr){

	uint8_t tmp[sizeof(struct bru_imsmem_t) + 7] = {0};
	struct bru_imsmem_t * imsmem_p = (struct bru_imsmem_t*)tmp;

	imsmem_p->drv_pid = *pid;
	imsmem_p->dev_addr = SPVKR_A;
	imsmem_p->ims_line = IMS_A;
	imsmem_p->addr = ZP_FREEBANK_ADDR | addr;
	imsmem_p->size = PARTITION_SIZE;
	
	union u_data{
		int8_t data[8];
		int64_t v_data;
	};

	union u_data digit;

	if(bru_readIMSMem(imsmem_p)){
		return ERR_READ_DATA;
	}else{
		for(int16_t i = 0; i < 8; i++){
			digit.data[i] = imsmem_p->data[i];
		}
		print_debug("Ячейка:[0x%0.8x] Данные: %5d\r\n", addr, digit.v_data);

	}
	
	return NO_ERROR;
}












