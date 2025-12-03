#ifndef __GSM_TYPEDEF_H__
#define __GSM_TYPEDEF_H__

/* ====================================== INCLDE HEADER ======================================= */
#include "stdint.h"
/* ============================================================================================ */

/* ====================================== DEFINTIONS ========================================== */
typedef enum {
    GSM_DECISION_STATE = 0,

    GSM_POWER_OFF_STATE,
    GSM_POWER_ON_STATE ,
    
    GSM_SYNC_AT_STATE,

    GSM_CONFIG_STATE,

    GSM_CHECK_SIM_STATE,

    GSM_REG_NETWORK_STATE,

    GSM_ATTACH_PSD,

    GSM_ACTIVATE_PDP,

    GSM_ERROR,
    GSM_READY
} gsm_state_t;

typedef struct {
    bool decision;
    bool power_off;
    bool power_on;
    bool sync_at;
    bool config;
    bool check_sim;
    bool reg_network;
    bool attach_psd;
    bool activate_pdp;
    bool error;
    bool ready;
} gsm_decision_flag_t;
/* ============================================================================================ */


/* ====================================== TYPEDEF DEFINITION ================================== */
/* ============================================================================================ */

#endif /* __GSM_TYPEDEF_H__ */