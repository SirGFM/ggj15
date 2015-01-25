/**
 * @file src/global.c
 */

#include <GFraMe/GFraMe_assets.h>
#include <GFraMe/GFraMe_audio.h>
#include <GFraMe/GFraMe_error.h>
#include <GFraMe/GFraMe_spriteset.h>
#include <GFraMe/GFraMe_texture.h>

#include <stdlib.h>

#include "global.h"

int gl_running;
GFraMe_spriteset *gl_sset8x8;
GFraMe_spriteset *gl_sset8x16;
GFraMe_spriteset *gl_sset16x16;
GFraMe_audio *gl_bgm;

GFraMe_texture gl_tex;
static GFraMe_spriteset _glSset8x8;
static GFraMe_spriteset _glSset8x16;
static GFraMe_spriteset _glSset16x16;
static GFraMe_audio gl_bgm_st;

GFraMe_ret gl_init() {
    GFraMe_ret rv;
    int atlas_w, atlas_h;
    unsigned char *data;
    
    atlas_w = 256;
    atlas_h = 64;
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
    
    GFraMe_spriteset_init
        (
         &_glSset8x16,
         &gl_tex,
         8,
         16
        );
    gl_sset8x16 = &_glSset8x16;
    
    GFraMe_spriteset_init
        (
         &_glSset8x8,
         &gl_tex,
         8,
         8
        );
    gl_sset8x8 = &_glSset8x8;
    
    rv = GFraMe_audio_init
        (
        &gl_bgm_st,
        "song",
        1,
        0,
        0
        );
    ASSERT(rv == GFraMe_ret_ok);
    gl_bgm = &gl_bgm_st;
    
    gl_running = 1;
    rv = GFraMe_ret_ok;
__ret:
    if (data)
        free(data);
    
    return rv;
}

void gl_clean() {
    GFraMe_audio_clear(&gl_bgm_st);
    GFraMe_texture_clear(&gl_tex);
}

