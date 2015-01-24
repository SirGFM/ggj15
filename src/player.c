/**
 * @file src/player.c
 */

#include <GFraMe/GFraMe_controller.h>
#include <GFraMe/GFraMe_sprite.h>

#include "global.h"
#include "player.h"

void pl_init(GFraMe_sprite *pl, int type) {
    GFraMe_sprite_init
        (
         pl,
         0, // x
         0, // y
         11, // phyx width
         6,  // phyx height
         gl_sset16x16, 
         0, // offset x
         0  // offset y
        );
    
    pl->id = type;
    pl->cur_tile = 0;
}

void pl_update(GFraMe_sprite *pl, int ms) {
    switch (pl->id) {
        case ID_PL1: {
            if (GFraMe_controllers) {
                if (GFraMe_controllers[0].lx < -0.3 || GFraMe_controllers[0].left) {
                    pl->obj.vx = -50;
                    pl->flipped = 1;
                }
                else if (GFraMe_controllers[0].lx > 0.3 || GFraMe_controllers[0].right) {
                    pl->obj.vx = 50;
                    pl->flipped = 0;
                }
                else
                    pl->obj.vx = 0;
            }
            else {
                // TODO keyboard controls
            }
        } break;
        case ID_PL2: {
            if (GFraMe_controllers) {
                if (GFraMe_controllers[0].rx < -0.3 || GFraMe_controllers[0].x) {
                    pl->obj.vx = -50;
                    pl->flipped = 1;
                }
                else if (GFraMe_controllers[0].rx > 0.3 || GFraMe_controllers[0].b) {
                    pl->obj.vx = 50;
                    pl->flipped = 0;
                }
                else
                    pl->obj.vx = 0;
            }
            else {
                // TODO keyboard controls
            }
        } break;
        default: return;
    }
    
    GFraMe_sprite_update(pl, ms);
}

void pl_draw(GFraMe_sprite *pl) {
    // TODO Account the camera
    GFraMe_sprite_draw(pl);
}

