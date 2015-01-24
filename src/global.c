/**
 * @file src/global.c
 */

#include <GFraMe/GFraMe_error.h>

#include "global.h"

int gl_running;

GFraMe_ret gl_init() {
    GFraMe_ret rv;
    
    gl_running = 1;
    rv = GFraMe_ret_ok;
//__ret:
    return rv;
}

void gl_clean() {
}

