#include "http_engine.h"

/* ====================================== GLOBAL VARIABLES ================================== */
uint8_t http_read_buff[HTTP_READ_BUFFER];

/* ========================================================================================== */

/* ================================== STATIC DECLARATIONS =================================== */
/* ========================================================================================== */

static bool http_init_entry(void){
    at_command_t cmd = {
        .cmd = "AT+HTTPINIT",
        .expect = "",
        .timeout_ms = 12000,
        .start_tick = get_systick_ms(),
        .cb = gsm_basic_callback
        };
    return send_at_cmd(cmd);
}
static bool http_init_wait(void){
    event_t event;
    static uint8_t timeout_count = 0;
    static uint8_t max_timeout = 3;
    if (!pop_event(&response_event_queue, &event))
        return false;

    switch (event.response)
    {
        case EVT_OK:
            DEBUG_PRINT("HTTPINIT SUCCESS\r\n");
            timeout_count = 0; 
            return true;


        case EVT_TIMEOUT:
            DEBUG_PRINT("HTTPINIT TIMEOUT\r\n");
            timeout_count++;
            if (timeout_count >= max_timeout){
                timeout_count = 0;
            }
            return false;
        

        case EVT_ERR:
            DEBUG_PRINT("HTTPINIT ERROR\r\n");
            timeout_count = 0;
            return false;
    }    
}

bool http_init(void){
    static uint8_t step = 0;
    bool tmp = false;
    switch (step)
    {
    case 0:
        tmp = http_init_entry();
        if (tmp){
            step++;
        }
        return false;
    
    case 1:
        if (http_init_wait()){
            step = 0;
            return true;
        }
        return false;
    }
    return false;
}


static bool http_term_entry(void){
    at_command_t cmd = {
        .cmd = "AT+HTTPTERM",
        .expect = "",
        .timeout_ms = 12000,
        .start_tick = get_systick_ms(),
        .cb = gsm_basic_callback
        };
    return send_at_cmd(cmd);
}
static bool http_term_wait(void){
    event_t event;
    static uint8_t timeout_count = 0;
    static uint8_t max_timeout = 3;
    if (!pop_event(&response_event_queue, &event))
        return false;

    switch (event.response)
    {
        case EVT_OK:
            DEBUG_PRINT("HTTPTERM SUCCESS\r\n");
            timeout_count = 0; 
            return true;


        case EVT_TIMEOUT:
            DEBUG_PRINT("HTTPTERM TIMEOUT\r\n");
            timeout_count++;
            if (timeout_count >= max_timeout){
                timeout_count = 0;
            }
            return false;
        

        case EVT_ERR:
            DEBUG_PRINT("HTTPTERM ERROR\r\n");
            timeout_count = 0;
            return false;
    }    
}

bool http_term(void){
    static uint8_t step = 0;
    bool tmp = false;
    switch (step)
    {
    case 0:
        tmp = http_term_entry();
        if (tmp){
            step++;
        }
        return false;
    
    case 1:
        if (http_term_wait()){
            step = 0;
            return true;
        }
        return false;
    }
    return false;
}

static bool http_seturl_entry(const char* url){
    at_command_t cmd = {
        .expect = "",
        .timeout_ms = 5000,
        .cb = gsm_basic_callback
    };
    snprintf(cmd.cmd, sizeof(cmd.cmd),"AT+HTTPPARA=\"URL\",\"%s\"", url);
    return send_at_cmd(cmd); 
}
static bool http_seturl_wait(){
    event_t event;
    static uint8_t timeout_count = 0;
    static uint8_t max_timeout = 3;
    if (!pop_event(&response_event_queue, &event))
        return false;
    switch (event.response)
    {
        case EVT_OK:
            DEBUG_PRINT("SET OK\r\n");
            return true;

        case EVT_TIMEOUT:
            timeout_count++;
            if (timeout_count >= max_timeout){
                timeout_count = 0;
            }
            return false;
        

        case EVT_ERR:
            timeout_count = 0;
            return false;
    }
    return false;
}

bool http_seturl(const char* url){
    static uint8_t step = 0;
    bool tmp = false;
    switch (step)
    {
    case 0:
        tmp = http_seturl_entry(url);
        if (tmp){
            step++;
        }
        return false;
    
    case 1:
        if (http_seturl_wait()){
            step = 0;
            return true;
        }
        return false;
    }
    return false;
}


bool http_action(uint8_t action){
    
}