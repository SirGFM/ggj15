/**
 * @file src/background.c
 */

#include <GFraMe/GFraMe_object.h>

#include "background.h"
#include "global.h"

#define MAX_COL 1

static GFraMe_object colliders[MAX_COL];

void bg_init() {
    GFraMe_object_clear(&colliders[0]);
	GFraMe_object_set_y(&colliders[0], 200);
    
    GFraMe_hitbox_set
        (
         &colliders[0].hitbox, 
         GFraMe_hitbox_upper_left,
         0,   // x
         0,   // y
         240, // w
         16   // h
        );
}

/**
 * Updates the current tilemap and its colliding objects according to the
 * camera position
 */
void bg_update() {
}

void bg_draw() {
    
}

/**
 * Get the list of active colliders
 * 
 * @param list Return the list of active colliders
 * @return How many objects where returned
 */
int bg_getColliders(GFraMe_object **list) {
    // TODO update this with to the camera
    *list = colliders;
    
    return 1;
}

