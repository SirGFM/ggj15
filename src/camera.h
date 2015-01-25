/**
 * @file src/camera.h
 */
#ifndef __CAMERA_H_
#define __CAMERA_H_

#include <GFraMe/GFraMe_sprite.h>

extern int cam_y;

void cam_init();
void cam_update(GFraMe_sprite *pl1, GFraMe_sprite *pl2);

#endif

