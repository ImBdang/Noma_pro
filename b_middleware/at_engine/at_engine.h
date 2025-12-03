#ifndef __AT_ENGINE_H__
#define __AT_ENGINE_H__

/* ====================================== INCLUDE HEADER ======================================= */
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "event.h"
#include "debug_driver.h"
#include "systick_api.h"
#include "hardware.h"
#include "lwrb.h"
#include "at_typedef.h"
/* ============================================================================================= */



/* ====================================== DEFINITIONS ========================================== */
extern  lwrb_t  usart_rb;
extern  uint8_t line_buff[LINE_BUFFER_SIZE];
/* ============================================================================================= */


/* ====================================== API ================================================== */
bool send_at_cmd(at_command_t cmd);
void at_engine_process(void);
void at_engine_init(void);
/* ============================================================================================= */

#endif /* __AT_ENGINE_H__ */