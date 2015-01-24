/**
 * @file src/global.h
 */
#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#include <GFraMe/GFraMe_error.h>

// Game initialization constants
#define WND_W 640
#define WND_H 480
#define SCR_W 320
#define SCR_H 240
#define ORG "com.gfmgamecorner"
#define NAME "game"
#define FPS 60
#define GAME_UFPS 60
#define GAME_DFPS 60

// Simple assert, if I ever want to use
#define ASSERT(stmt) \
  do { \
    if (!(stmt)) \
      goto __ret; \
  } while (0)

// Global variables
extern int gl_running;

// Functions

GFraMe_ret gl_init();
void gl_clean();

#endif

