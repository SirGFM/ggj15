/**
 * @file src/player.c
 */

#include <GFraMe/GFraMe_controller.h>
#include <GFraMe/GFraMe_sprite.h>
#include <GFraMe/GFraMe_spriteset.h>

#include "global.h"
#include "player.h"

void pl_init(GFraMe_sprite *pl, int type) {
    GFraMe_sprite_init
        (
         pl,
         0, // x
         0, // y
         6,   // phyx width
         11,  // phyx height
         gl_sset16x16, 
         0, // offset x
         0  // offset y
        );
    
    GFraMe_hitbox_set
        (
         &pl->obj.hitbox,
         GFraMe_hitbox_upper_left,
         4, // x
         2, // y
         6, // w
         11 // h
        );
    
    pl->id = type;
    pl->cur_tile = 16;
    pl->obj.ay = 500;
}

void pl_update(GFraMe_sprite *pl, int ms) {
    switch (pl->id) {
        case ID_PL1: {
            if (GFraMe_controllers) {
                // Horizontal movement
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
                // Jump
                if ((pl->obj.hit & GFraMe_direction_down)
                    &&  GFraMe_controllers[0].l1)
                    pl->obj.vy = -150;
            }
            else {
                // TODO keyboard controls
            }
        } break;
        case ID_PL2: {
            if (GFraMe_controllers) {
                // Horizontal movement
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
                // Jump
                if ((pl->obj.hit & GFraMe_direction_down)
                    &&  GFraMe_controllers[0].r1)
                    pl->obj.vy = -150;
            }
            else {
                // TODO keyboard controls
            }
        } break;
        default: return;
    }
    
    if (pl->obj.hit & GFraMe_direction_down)
       pl->obj.ay = 0; 
    else
        pl->obj.ay = 500;
    
    GFraMe_sprite_update(pl, ms);
}

void pl_draw(GFraMe_sprite *pl) {
    int ox, oy;
    
    // TODO Account the camera
    switch (pl->cur_tile) {
        case 0: {
            ox = 4;
            oy = 2;
        } break;
        default: {
            ox = 0;
            oy = 0;
        }
    }
    
    GFraMe_spriteset_draw
        (
         pl->sset,
         pl->cur_tile,
         pl->obj.x + ox,
         pl->obj.y + oy,
         pl->flipped
        );
}

