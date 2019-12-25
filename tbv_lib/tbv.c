#include "tbv.h"
#include "libbru.h"

uint64_t get_tbv_time(void){
    //union u_reg_t reg_t;
    //const uint32_t tbv_1khz_reg_size = 8;
    //reg_t.reg_64 = 0;
    PROCESS drv_pid = 0;
	uint64_t tbv_time=0;

    uint8_t tmp[sizeof(struct bru_imsmem_t) + sizeof(tbv_time) - 1 ]={0};
	struct bru_imsmem_t *bru_imsmem_p= (struct bru_imsmem_t*)tmp;

    if(bru_getPID("regio_bg", &drv_pid) == 1){
        return 0;
    }

    bru_imsmem_p->drv_pid     = drv_pid;
    bru_imsmem_p->dev_addr    = SPVKR_A;
    bru_imsmem_p->ims_line    = IMS_A;
    bru_imsmem_p->addr        = TBV_1kHz_ADDR;
    bru_imsmem_p->size        = sizeof(tbv_time);

	switch(bru_readIMSMem(bru_imsmem_p))
	{
		case 1:
			print_debug("Не удалось прочитать регистр счетчика\r\n");
		break;

		case 0:
			memcpy(&tbv_time, bru_imsmem_p->data, sizeof(tbv_time));
		break;

		default:
			print_debug("Unexpected error!\r\n");
		break;
	}

    return tbv_time;
}

//uint64_t set_tbv_time(uint64_t data)										//записывает время в регистр счетчика 1 кГц ТБВ (время)
//{
//    PROCESS  drv_pid = 0;
//
//	if (bru_getPID("regio_bg", &drv_pid))
//        return 0;
//
//    //struct bru_imsmem_t *bru_imsmem;
//
//    uint8_t tmp[sizeof(struct bru_imsmem_t) + sizeof(data) -1 ]={0};
//   	struct bru_imsmem_t *bru_imsmem_p= (struct bru_imsmem_t*)tmp;
//
//    //bru_imsmem = malloc(sizeof(struct bru_imsmem_t) + sizeof(data)-1);
//    bru_imsmem_p->drv_pid      	= drv_pid;
//    bru_imsmem_p->dev_addr		= SPVKR_A;
//    bru_imsmem_p->ims_line		= IMS_A;
//    bru_imsmem_p->size			= sizeof(data);
//    bru_imsmem_p->addr			= TBV_TIME_ADDR;
//
//    memcpy(bru_imsmem_p->data, &data, sizeof(data));
//
//    bru_writeIMSMem(bru_imsmem_p);											//запись данных в ТБВ
//
//   // free(bru_imsmem);
//	return 0;
//}
//
//
//


