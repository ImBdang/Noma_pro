#ifndef __AT_TYPEDEF_H__
#define __AT_TYPEDEF_H__

/* ====================================== INCLDE HEADER ======================================= */
#include "stdint.h"
#include "callback_typedef.h"
/* ============================================================================================ */

/* ====================================== DEFINTIONS ========================================== */
#define LINE_BUFFER_SIZE    1024
#define LWRB_BUFFER_SIZE    1024
/* ============================================================================================ */


/* ====================================== TYPEDEF DEFINITION ================================== */
typedef enum {
    OK_RESP,
    ERROR_RESP,
    TIMEOUT_RESP,
    PRIMARY,
    INTERMEDIATE
} response_status_t;

typedef struct {
    char cmd[128];                                                  /*<! AT command */
    char expect[32];                                                /*<! AT expect response */
    uint32_t timeout_ms;                                            /*<! Timeout for command */
    uint32_t start_tick;                                            /*<! Started time when send */
    gsm_callback cb;                                                /*<! Callback handle the command */
} at_command_t;
/* ============================================================================================ */

#endif /* __AT_TYPEDEF_H__ */