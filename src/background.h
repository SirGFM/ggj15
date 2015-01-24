/**
 * @file src/background.h
 */
#ifndef __BACKGROUND_H_
#define __BACKGROUND_H_

#include <GFraMe/GFraMe_object.h>

void bg_init();
/**
 * Updates the current tilemap and its colliding objects according to the
 * camera position
 */
void bg_update();
void bg_draw();

/**
 * Get the list of active colliders
 * 
 * @param list Return the list of active colliders
 * @return How many objects where returned
 */
int bg_getColliders(GFraMe_object **list);

#endif

