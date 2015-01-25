/**
 * @file src/player.c
 */

#include <GFraMe/GFraMe_animation.h>
#include <GFraMe/GFraMe_controller.h>
#include <GFraMe/GFraMe_sprite.h>
#include <GFraMe/GFraMe_spriteset.h>

#include "background.h"
#include "camera.h"
#include "global.h"
#include "player.h"

#define PL_TILE0 64

void pl_init(GFraMe_sprite *pl, int type) {
    int y;
    
    y = bg_getHeight() - 32;
    
    GFraMe_sprite_init
        (
         pl,
         0, // x
         y, // y
         6,   // phyx width
         11,  // phyx height
         gl_sset8x16, 
         0, // offset x
         0  // offset y
        );
    
    if (type == ID_PL1)
        GFraMe_object_set_x(&pl->obj, 16);
    else if (type == ID_PL2)
        GFraMe_object_set_x(&pl->obj, SCR_W - 32);
    
    GFraMe_hitbox_set
        (
         &pl->obj.hitbox,
         GFraMe_hitbox_upper_left,
         0, // x
         0, // y
         6, // w
         11 // h
        );
    
    pl->cur_tile = PL_TILE0;
    pl->id = type;
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
                if (GFraMe_controllers[0].rx < -0.3
                    || GFraMe_controllers[0].x) {
                    pl->obj.vx = -50;
                    pl->flipped = 1;
                }
                else if (GFraMe_controllers[0].rx > 0.3
                         || GFraMe_controllers[0].b) {
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
    
    if (pl->obj.hit & GFraMe_direction_down) {
        pl->obj.ay = 0;
    }
    else {
        pl->obj.ay = 500;
    }
    
    GFraMe_sprite_update(pl, ms);
}

void pl_draw(GFraMe_sprite *pl) {
    int oy;
    
    // TODO Account the camera
    switch (pl->cur_tile) {
        case 0 + PL_TILE0: {
            oy = 0;
        } break;
        case 1 + PL_TILE0: {
            oy = -2;
        } break;
        default: {
            oy = 0;
        }
    }
    
    GFraMe_spriteset_draw
        (
         pl->sset,
         pl->cur_tile,
         pl->obj.x,
         pl->obj.y + oy - cam_y,
         pl->flipped
        );
}

