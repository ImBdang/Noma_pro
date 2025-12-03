#include "processor.h"

/* ================================== STATIC DECLARATIONS =================================== */

/* =========================================================================================== */

void processor_init(void){
    hardware_init();
    at_engine_init();
}

void processor(void){
    at_engine_process();        /*<! Parse and get line command */
    gsm_process();              /*<! Finite State Machine GSM */
}