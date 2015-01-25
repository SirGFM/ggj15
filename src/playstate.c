/**
 * @file src/playstate.c
 */

#include <GFraMe/GFraMe_error.h>
#include <GFraMe/GFraMe_event.h>
#include <GFraMe/GFraMe_object.h>

#include "background.h"
#include "camera.h"
#include "global.h"
#include "playstate.h"
#include "player.h"

GFraMe_event_setup();

static void ps_init();
static void ps_event();
static void ps_update();
static void ps_draw();

static GFraMe_sprite pl1, pl2;
static GFraMe_object lWall, rWall;

void playstate() {
    ps_init();
    
    GFraMe_event_init(GAME_UFPS, GAME_DFPS);
    while (gl_running) {
        // F*** yeah, bug button!!
        if (GFraMe_controller_max > 0
            && (GFraMe_controllers[0].select || GFraMe_controllers[0].start)
            || GFraMe_keys.r)
            ps_init();
        ps_event();
        ps_update();
        ps_draw();
    }
}

static void ps_init() {
    pl_init(&pl1, ID_PL1);
    pl_init(&pl2, ID_PL2);
    
    bg_init();
    cam_init();
    
    GFraMe_object_clear(&lWall);
    GFraMe_hitbox_set
        (
         &lWall.hitbox,
         GFraMe_hitbox_upper_left,
         0,    // x
         0,    // y
         8,    // w
         bg_getHeight() // h
        );
    
    GFraMe_object_clear(&rWall);
    GFraMe_object_set_x(&rWall, SCR_W - 8);
    GFraMe_hitbox_set
        (
         &rWall.hitbox,
         GFraMe_hitbox_upper_left,
         0,    // x
         0,    // y
         8,    // w
         bg_getHeight() // h
        );
    
}

static void ps_update() {
  GFraMe_event_update_begin();
     GFraMe_object *list;
     GFraMe_ret rv;
     int count, i, pl1_on_floor, pl2_on_floor, teleport1, teleport2;
     
     pl_update(&pl1, GFraMe_event_elapsed);
     pl_update(&pl2, GFraMe_event_elapsed);
     
     bg_update();
     
     count = bg_getColliders(&list);
     i = 0;
     while (i < count) {
         // Collide the players against the floor
         if (!(pl1.obj.hit & GFraMe_direction_down)) {
             rv = GFraMe_object_overlap(&list[i], &pl1.obj, GFraMe_dont_collide);
             if (rv == GFraMe_ret_ok) {
                 GFraMe_object_set_y
                     (
                      &pl1.obj,
                      list[i].y - pl1.obj.hitbox.hh - pl1.obj.hitbox.cy
                     );
                 pl1.obj.vy = 0;
             }
         }
         if (!(pl2.obj.hit & GFraMe_direction_down)) {
             rv = GFraMe_object_overlap(&list[i], &pl2.obj, GFraMe_dont_collide);
             if (rv == GFraMe_ret_ok) {
                 GFraMe_object_set_y
                     (
                      &pl2.obj,
                      list[i].y - pl2.obj.hitbox.hh - pl2.obj.hitbox.cy
                     );
                 pl2.obj.vy = 0;
             }
         }
         // If both players are colliding, stop
         if ((pl1.obj.hit & GFraMe_direction_down)
             && (pl2.obj.hit & GFraMe_direction_down))
             break;
         i++;
     }
     
     // Collide against the wall
     GFraMe_object_overlap(&lWall, &pl1.obj, GFraMe_first_fixed);
     GFraMe_object_overlap(&rWall, &pl1.obj, GFraMe_first_fixed);
     GFraMe_object_overlap(&lWall, &pl2.obj, GFraMe_first_fixed);
     GFraMe_object_overlap(&rWall, &pl2.obj, GFraMe_first_fixed);
     
     pl1_on_floor = (pl1.obj.hit & GFraMe_direction_down);
     pl2_on_floor = (pl2.obj.hit & GFraMe_direction_down);
     
     // Then collide them against each other
     rv = GFraMe_object_overlap(&pl1.obj, &pl2.obj, GFraMe_dont_collide);
     if (rv == GFraMe_ret_ok) {
         if (!pl1_on_floor && (pl1.obj.hit & GFraMe_direction_down)) {
             GFraMe_object_set_y
                 (
                  &pl1.obj,
                  pl2.obj.y - pl1.obj.hitbox.hh - pl1.obj.hitbox.cy
                 );
             pl1.obj.vy = 0;
             pl1.obj.ay = 0;
         }
         else if (!pl2_on_floor&& (pl2.obj.hit & GFraMe_direction_down)) {
             GFraMe_object_set_y
                 (
                  &pl2.obj,
                  pl1.obj.y - pl2.obj.hitbox.hh - pl2.obj.hitbox.cy
                 );
             pl2.obj.vy = 0;
             pl2.obj.ay = 0;
         }
     }
     
     if (GFraMe_controller_max == 1) {
        teleport1 = GFraMe_controllers[0].l2;
        teleport2 = GFraMe_controllers[0].r2;
     }
     else if (GFraMe_controller_max >= 1) {
        teleport1 = GFraMe_controllers[0].b || GFraMe_controllers[0].x;
        teleport2 = GFraMe_controllers[1].b || GFraMe_controllers[1].x;
     }
     else {
        teleport1 = GFraMe_keys.s;
        teleport2 = GFraMe_keys.down;
     }
     // Woooooooooo, teleport!!
     if (teleport1 || teleport2) {
        GFraMe_object *fixed, *tgt;
        int ay, vx, vy;
        
        if (teleport1) {
            fixed = &pl1.obj;
            tgt = &pl2.obj;
        }
        else if (teleport2) {
            fixed = &pl2.obj;
            tgt = &pl1.obj;
        }
        ay = tgt->ay;
        vx = tgt->vx;
        vy = tgt->vy;
        GFraMe_object_set_pos(tgt, fixed->x, fixed->y);
        tgt->ay = ay;
        tgt->vx = vx;
        tgt->vy = vy;
        if (fixed->hit & GFraMe_direction_down)
            tgt->vy = 0;
        tgt->hit |= GFraMe_direction_down;
     }
     
   GFraMe_event_update_end();
}

static void ps_draw() {
    GFraMe_event_draw_begin();
      cam_update(&pl1, &pl2);
      
      bg_draw();
      pl_draw(&pl1);
      pl_draw(&pl2);
    GFraMe_event_draw_end();
}

static void ps_event() {
    GFraMe_event_begin();
        GFraMe_event_on_timer();
        GFraMe_event_on_mouse_up();
        GFraMe_event_on_mouse_down();
        GFraMe_event_on_mouse_moved();
//        GFraMe_event_on_finger_down();
//        GFraMe_event_on_finger_up();
        GFraMe_event_on_key_down();
            if (GFraMe_keys.esc)
                gl_running = 0;
        GFraMe_event_on_key_up();
        GFraMe_event_on_controller();
            if (GFraMe_controller_max > 0 && GFraMe_controllers[0].home)
                gl_running = 0;
//        GFraMe_event_on_bg();
//        GFraMe_event_on_fg();
        GFraMe_event_on_quit();
            gl_running = 0;
    GFraMe_event_end();
}

