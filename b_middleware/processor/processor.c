#include "processor.h"

/* ================================== STATIC DECLARATIONS =================================== */

/* =========================================================================================== */

void processor_init(void){
    hardware_init();
    at_engine_init();
}

void processor(void){
    static bool flag = true;
    at_engine_process();        /*<! Parse and get line command */
    gsm_process();              /*<! Finite State Machine GSM */
    if (gsm_is_ready()){
        if (flag){
            http_term();
            delay_ms(500);
            if (!http_init())
                return;
            delay_ms(300);
            if (http_term())
                flag = false;
            breakp();
        }
    }
}