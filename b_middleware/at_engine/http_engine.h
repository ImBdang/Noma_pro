#ifndef __HTTP_ENGINE_H__
#define __HTTP_ENGINE_H__

/* ====================================== INCLUDE HEADER ======================================= */
#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"
#include "debug_driver.h"
#include "at_engine.h"
#include "http_typedef.h"
#include "gsm_callback.h"
/* ============================================================================================= */



/* ====================================== VARIABLES ============================================ */
extern uint8_t http_read_buff[HTTP_READ_BUFFER];
/* ============================================================================================= */


/* ====================================== API ================================================== */
bool http_init(void);
bool http_term(void);
bool http_seturl(const char* url);
bool http_action(uint8_t action);
/* ============================================================================================= */

#endif /* __HTTP_ENGINE_H__ */