#include "string_handler.h"

/**
 * @brief   Convert char to uint_t
 * 
 * @param   s: String that you need to convert to uint32_t
 * 
 * @retval  Uint32_t after converted
 */
uint32_t fast_atoi(const char *s) {
    uint32_t v = 0;
    while (*s >= '0' && *s <= '9') {
        v = v * 10 + (*s - '0');
        s++;
    }
    return v;
}

/**
 * @brief   Convert uint32_t to char[11]
 * 
 * @param   value: Number that you want to convert
 * @param   buf:   Pointer to char array hold the converted number in string
 */
void fast_itoa(uint32_t value, char *buf) {
    char temp[11]; 
    int i = 0;
    if (value == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return buf;
    }
    while (value > 0) {
        temp[i++] = (value % 10) + '0';
        value /= 10;
    }
    int j = 0;
    while (i > 0) {
        buf[j++] = temp[--i];
    }
    buf[j] = '\0';
}


/**
 * @brief   Dispatch PRIMARY response as like +CPIN: READY
 * 
 * @param   str: Line response
 * @param   result: Variable that hold the result
 */
void primary_dispatch(const char* str, char* result)
{
    if (str == NULL || result == NULL) {
        return;
    }

    const char *p = strchr(str, ':');
    if (!p) {
        result[0] = '\0';
        return;
    }

    p++; 
    while (*p == ' ' || *p == '\t') {
        p++;
    }

    while (*p != '\0' && *p != '\r' && *p != '\n') {
        *result++ = *p++;
    }
    *result = '\0';
}