/**
 * @file src/player.c
 */

#include <GFraMe/GFraMe_animation.h>
#include <GFraMe/GFraMe_controller.h>
#include <GFraMe/GFraMe_keys.h>
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
    int isLeft, isRight, didJump;
    
    didJump = pl->obj.hit & GFraMe_direction_down;
    switch (pl->id) {
        case ID_PL1: {
            // Get controls
            if (GFraMe_controller_max == 1) {
                isLeft = GFraMe_controllers[0].lx < -0.3 || GFraMe_controllers[0].left;
                isRight = GFraMe_controllers[0].lx > 0.3 || GFraMe_controllers[0].right;
                didJump &= GFraMe_controllers[0].l1;
            }
            else if (GFraMe_controller_max >= 2) {
                isLeft = GFraMe_controllers[0].lx < -0.3 || GFraMe_controllers[0].left;
                isRight = GFraMe_controllers[0].lx > 0.3 || GFraMe_controllers[0].right;
                didJump &= GFraMe_controllers[0].a;
            }
            else {
                isLeft = GFraMe_keys.a;
                isRight= GFraMe_keys.d;
                didJump &= GFraMe_keys.w;
            }
        } break;
        case ID_PL2: {
            // Get controls
            if (GFraMe_controller_max == 1) {
                isLeft = GFraMe_controllers[0].rx < -0.3 || GFraMe_controllers[0].x;
                isRight = GFraMe_controllers[0].rx > 0.3 || GFraMe_controllers[0].b;
                didJump &= GFraMe_controllers[0].r1;
            }
            else if (GFraMe_controller_max >= 2) {
                isLeft = GFraMe_controllers[1].lx < -0.3 || GFraMe_controllers[1].left;
                isRight = GFraMe_controllers[1].lx > 0.3 || GFraMe_controllers[1].right;
                didJump &= GFraMe_controllers[1].a;
            }
            else {
                isLeft = GFraMe_keys.left;
                isRight= GFraMe_keys.right;
                didJump &= GFraMe_keys.up;
            }
        } break;
        default: return;
    }
    if (isLeft) {
        pl->obj.vx = -50;
        pl->flipped = 1;
    }
    else if (isRight) {
        pl->obj.vx = 50;
        pl->flipped = 0;
    }
    else {
        pl->obj.vx = 0;
    }
    
    if (didJump) {
        pl->obj.vy = -150;
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

