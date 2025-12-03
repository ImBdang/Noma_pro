#include "at_engine.h"

/* ================================== STATIC DECLARATIONS =================================== */
static lwrb_buffer[LWRB_BUFFER_SIZE];   /*<! Buffer for lwrb that store usart rx */
static bool is_busy = false;            /*<! Flag to know any AT command is sending */
static at_command_t executing_cmd;      /*<! Executing AT command */

static void handle_response_line(const char *line);
static void handle_urc_line(const char *urc);
static void line_parse(void);
/* =========================================================================================== */

/**
 * @brief   Send AT command
 * 
 * @param   cmd: Struct that description command as liek expect response, command, ...
 * 
 * @note    Callback func will handler the response, dont need to process response in this func
 *          We only need to make sure that setup the params as like start time then send through USART
 * 
 * @retval  true if send success
 * @retval  false is send not success (mostly is_busy is true, other command is still wating for response)
 */
bool modem_send_at_cmd(at_command_t cmd){
    if (is_busy)
        return false;
    executing_cmd = cmd;
    executing_cmd.start_tick = get_systick_ms();
    is_busy = true;

    usart_sendstring(SIM_USART_PORT, executing_cmd.cmd);
    usart_sendstring(SIM_USART_PORT, "\r\n");
    DEBUG_PRINT(">>");
    DEBUG_PRINT(executing_cmd.cmd);
    DEBUG_PRINT("\r\n");
    return true;
}

void at_engine_init(void){
    hardware_init();
    lwrb_init(&usart_rb, lwrb_buffer, sizeof(lwrb_buffer));
}