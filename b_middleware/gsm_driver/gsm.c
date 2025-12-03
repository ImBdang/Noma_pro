#include "gsm.h"

/* ================================== STATIC DECLARATIONS =================================== */
static gsm_state_t gsm_cur_state = GSM_DECISION_STATE;      /*<! Current state of gsm state machine */
static gsm_decision_flag_t decision_flag;

/*<! Clear decision flags */
static void clear_decision_flags(void);

/*<! Those func for each state */
static void process_gsm_decision_state(void);
static void process_gsm_power_off_state(void);
static void process_gsm_power_on_state(void);
static void process_gsm_sync_at_state(void);
static void process_gsm_config_state(void);
static void process_gsm_check_sim_state(void);
static void process_gsm_reg_network_state(void);
static void process_gsm_attach_psd_state(void);
static void process_gsm_activate_pdp_state(void);
static void process_gsm_error_state(void);
static void process_gsm_ready_state(void);
/* =========================================================================================== */

/**
 * @brief   Clear decision flags
 */
static void clear_decision_flags(void)
{
    decision_flag.power_off     = false;
    decision_flag.power_on      = false;
    decision_flag.sync_at       = false;
    decision_flag.config        = false;
    decision_flag.check_sim     = false;
    decision_flag.reg_network   = false;
    decision_flag.attach_psd    = false;
    decision_flag.activate_pdp  = false;
    decision_flag.error         = false;
    decision_flag.ready         = false;
}


/**
 * @brief   Power off modem
 */
bool gsm_power_off(void){
    static uint8_t step = 0;
    static uint32_t t0 = 0;

    switch (step)
    {
        case 0:
            SIM_PWKEY_LOW();
            t0 = get_systick_ms();
            step = 1;
            DEBUG_PRINT("POWERING OFF, PWKEY LOW 2.5s\r\n");
            return false;

        case 1:
            if (get_systick_ms() - t0 < 2500)
                return false;
            SIM_PWKEY_HIGH();
            t0 = get_systick_ms();
            step = 2;
            DEBUG_PRINT("POWERING OFF, PWKEY HIGH about 8.9s\r\n");
            return false;

        case 2:
            if (!SIM_STATUS_READ()){
                DEBUG_PRINT("STATUS is LOW, MODEM is now OFFLINE\r\n");
                step = 0;
                return true;
            }
            if (get_systick_ms() - t0 > 8900) {
                step = 0;                     
                DEBUG_PRINT("TIMEOUT, reset to step 0\r\n");
                return false;
            }
            DEBUG_PRINT("Waiting STATUS OFF\r\n");
            return false;
        
        default:
            break;
    }
    return false;
}


/**
 * @brief   Power on modem
 */
bool gsm_power_on(void)
{
    static uint8_t step = 0;
    static uint32_t t0 = 0;

    switch (step)
    {
        case 0:
            SIM_PWKEY_LOW();
            t0 = get_systick_ms();
            step = 1;
            DEBUG_PRINT("POWERING ON, PWKEY LOW 50ms\r\n");
            return false;

        case 1:
            if (get_systick_ms() - t0 < 50)
                return false;
            SIM_PWKEY_HIGH();
            t0 = get_systick_ms();
            step = 2;
            DEBUG_PRINT("POWERING ON, PWKEY HIGH about 8.5s\r\n");
            return false;

        case 2:
            if (SIM_STATUS_READ()){
                DEBUG_PRINT("STATUS is HIGH, MODEM is now ONLINE\r\n");
                step = 0;
                return true;
            }
            if (get_systick_ms() - t0 > 8500) {
                step = 0;                   
                DEBUG_PRINT("TIMEOUT, reset to step 0\r\n");
                return false;
            }
            DEBUG_PRINT("Waiting STATUS ON\r\n");
            return false;
        
        default:
            break;
    }
    return false;
}

/**
 * @brief   Reset by turn off then turn on
 */
bool gsm_power_reset(void){
    static uint8_t step = 0;
    bool tmp = false;
    switch (step)
    {
    case 0:
        tmp = gsm_power_off();
        if (tmp){
            step++;
        }
        return false;
    
    case 1:
        tmp = gsm_power_on();
        if (tmp){
            step = 0;
            return true;
        }
        return false;
    }
    return false;
}


/**
 * @brief   Change state by this decision func
 * 
 * @note    If that state flag is false that mean its not done yet so switch to it
 */
static void process_gsm_decision_state(void)
{
    /*<! STATE: ERROR */
    if (!decision_flag.error) {
        gsm_cur_state = GSM_ERROR;
        return;
    }

    /*<! STATE: POWER_OFF */
    // if (!decision_flag.power_off) {
    //     gsm_cur_state = GSM_POWER_OFF_STATE;
    //     return;
    // }

    /*<! STATE: POWER_ON */
    if (!decision_flag.power_on) {
        gsm_cur_state = GSM_POWER_ON_STATE;
        return;
    }

    /*<! STATE: SYNC_AT */
    if (!decision_flag.sync_at) {
        gsm_cur_state = GSM_SYNC_AT_STATE;
        return;
    }

    /*<! STATE: CONFIG */
    if (!decision_flag.config) {
        gsm_cur_state = GSM_CONFIG_STATE;
        return;
    }

    /*<! STATE: CHECK_SIM */
    if (!decision_flag.check_sim) {
        gsm_cur_state = GSM_CHECK_SIM_STATE;
        return;
    }

    /*<! STATE: REG_NETWORK */
    if (!decision_flag.reg_network) {
        gsm_cur_state = GSM_REG_NETWORK_STATE;
        return;
    }

    /*<! STATE: ATTACH_PSD */
    if (!decision_flag.attach_psd) {
        gsm_cur_state = GSM_ATTACH_PSD;
        return;
    }

    /*<! STATE: ACTIVATE_PDP */
    if (!decision_flag.activate_pdp) {
        gsm_cur_state = GSM_ACTIVATE_PDP;
        return;
    }

    /*<! STATE: READY */
    if (!decision_flag.ready) {
        gsm_cur_state = GSM_READY;
        return;
    }
}



/*<! GSM_POWER_OFF_STATE ---------------------------------------------*/
static void process_gsm_power_off_state(void)
{
    // TODO: Your logic here
}


/*<! GSM_POWER_ON_STATE ----------------------------------------------*/
static void process_gsm_power_on_state(void)
{
    // TODO: Your logic here
}


/*<! GSM_SYNC_AT_STATE ------------------------------------------------*/
static void process_gsm_sync_at_state(void)
{
    // TODO: Your logic here
}


/*<! GSM_CONFIG_STATE -------------------------------------------------*/
static void process_gsm_config_state(void)
{
    // TODO: Your logic here
}


/*<! GSM_CHECK_SIM_STATE ----------------------------------------------*/
static void process_gsm_check_sim_state(void)
{
    // TODO: Your logic here
}


/*<! GSM_REG_NETWORK_STATE --------------------------------------------*/
static void process_gsm_reg_network_state(void)
{
    // TODO: Your logic here
}


/*<! GSM_ATTACH_PSD ---------------------------------------------------*/
static void process_gsm_attach_psd_state(void)
{
    // TODO: Your logic here
}


/*<! GSM_ACTIVATE_PDP -------------------------------------------------*/
static void process_gsm_activate_pdp_state(void)
{
    // TODO: Your logic here
}


/*<! GSM_ERROR --------------------------------------------------------*/
static void process_gsm_error_state(void)
{
    // TODO: Your logic here
}


/*<! GSM_READY --------------------------------------------------------*/
static void process_gsm_ready_state(void)
{
    // TODO: Your logic here
}


void gsm_process(void){
    switch (gsm_cur_state)
    {
    case GSM_DECISION_STATE:
        process_gsm_decision_state();
        break;

    case GSM_POWER_OFF_STATE:
        process_gsm_power_off_state();
        break;

    case GSM_POWER_ON_STATE:
        process_gsm_power_on_state();
        break;

    case GSM_SYNC_AT_STATE:
        process_gsm_sync_at_state();
        break;

    case GSM_CONFIG_STATE:
        process_gsm_config_state();
        break;

    case GSM_CHECK_SIM_STATE:
        process_gsm_check_sim_state();
        break;

    case GSM_REG_NETWORK_STATE:
        process_gsm_reg_network_state();
        break;

    case GSM_ATTACH_PSD:
        process_gsm_attach_psd_state();
        break;

    case GSM_ACTIVATE_PDP:
        process_gsm_activate_pdp_state();
        break;

    case GSM_ERROR:
        process_gsm_error_state();
        break;

    case GSM_READY:
        process_gsm_ready_state();
        break;
    }
}