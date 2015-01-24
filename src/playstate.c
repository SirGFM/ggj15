/**
 * @file src/playstate.c
 */

#include <GFraMe/GFraMe_event.h>

#include "global.h"
#include "playstate.h"

GFraMe_event_setup();

static void ps_init();
static void ps_event();
static void ps_update();
static void ps_draw();

void playstate() {
    ps_init();
    while (gl_running) {
        ps_event();
        ps_update();
        ps_draw();
    }
}

static void ps_init() {
    GFraMe_event_init(GAME_UFPS, GAME_DFPS);
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

static void ps_update() {
    GFraMe_event_update_begin();
    GFraMe_event_update_end();
}

static void ps_draw() {
    GFraMe_event_draw_begin();
    GFraMe_event_draw_end();
}

