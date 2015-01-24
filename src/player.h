/**
 * @file src/player.h
 */
#ifndef __PLAYER_H_
#define __PLAYER_H_

#include <GFraMe/GFraMe_sprite.h>

void pl_init(GFraMe_sprite *pl, int type);
void pl_update(GFraMe_sprite *pl, int ms);
void pl_draw(GFraMe_sprite *pl);

#endif

