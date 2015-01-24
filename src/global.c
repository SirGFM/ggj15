/**
 * @file src/global.c
 */

#include <GFraMe/GFraMe_assets.h>
#include <GFraMe/GFraMe_error.h>
#include <GFraMe/GFraMe_spriteset.h>
#include <GFraMe/GFraMe_texture.h>

#include <stdlib.h>

#include "global.h"

int gl_running;
GFraMe_spriteset *gl_sset16x16;

GFraMe_texture gl_tex;
static GFraMe_spriteset _glSset16x16;

GFraMe_ret gl_init() {
    GFraMe_ret rv;
    int atlas_w, atlas_h;
    unsigned char *data;
    
    atlas_w = 128;
    atlas_h = 128;
    data = 0;
    
    GFraMe_texture_init(&gl_tex);
    
    rv = GFraMe_assets_buffer_image
        (
         "atlas",
         atlas_w,
         atlas_h,
         (char**)&data
        );
    GFraMe_assertRet(rv == GFraMe_ret_ok, "Buffering image failed", __ret);
    
    rv = GFraMe_texture_load
        (
         &gl_tex,
         atlas_w,
         atlas_h,
         data
        );
    GFraMe_assertRet(rv == GFraMe_ret_ok, "Loading texture failed", __ret);
    
    GFraMe_spriteset_init
        (
         &_glSset16x16,
         &gl_tex,
         16,
         16
        );
    gl_sset16x16 = &_glSset16x16;
    
    gl_running = 1;
    rv = GFraMe_ret_ok;
__ret:
    if (data)
        free(data);
    
    return rv;
}

void gl_clean() {
    GFraMe_texture_clear(&gl_tex);
}

