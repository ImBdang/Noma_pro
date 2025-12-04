#include "processor.h"

/* ================================== STATIC DECLARATIONS =================================== */

/* =========================================================================================== */

void processor_init(void){
    hardware_init();
    at_engine_init();
}

void processor(void){
    static uint8_t step = 0;
    static bool flag = true;
    at_engine_process();        /*<! Parse and get line command */
    gsm_process();              /*<! Finite State Machine GSM */
    if (gsm_is_ready()){
        if (flag){
            switch (step)
            {
                case 0:
                    if (http_init())
                        step++;
                    else 
                        http_term();
                    break;
                
                case 1:
                    if (http_seturl(url))
                        step++;
                    break;

                case 2:
                    if (http_action(0))
                        step++;
                    break;
                
                case 3:
                    if (http_read(0, 1024)){
                        step++;
                        DEBUG_PRINT("PROCESS DONE\r\n");
                    }
                    break;
                
                case 4:
                    flag = false;
                    break;

            }
            delay_ms(200);
        }
    }
}