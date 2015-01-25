/**
 * @file src/camera.c
 */

#include <GFraMe/GFraMe_sprite.h>

#include "background.h"
#include "camera.h"
#include "global.h"

int cam_y;

void cam_init() {
    cam_y = bg_getHeight() - SCR_H;
    
    if (cam_y < 0)
        cam_y = 0;
}

void cam_update(GFraMe_sprite *pl1, GFraMe_sprite *pl2) {
    #define getLocalY(spr) \
        (spr->obj.y - cam_y)
    
    #define setLocalY(spr) \
      do { \
        cam_y = spr->obj.y - SCR_H / 2; \
        if (cam_y < 0) { \
            cam_y = 0; \
        } \
      } while (0)
    
    if (getLocalY(pl1) < SCR_H / 2)
        setLocalY(pl1);
    
    if (getLocalY(pl2) < SCR_H / 2)
        setLocalY(pl2);
}

