/**
 * @file src/global.h
 */
#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#include <GFraMe/GFraMe_error.h>
#include <GFraMe/GFraMe_spriteset.h>

// Game initialization constants
#define WND_W 480
#define WND_H 640
#define SCR_W 120
#define SCR_H 160
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
extern GFraMe_spriteset *gl_sset8x8;
extern GFraMe_spriteset *gl_sset16x16;

// Functions

GFraMe_ret gl_init();
void gl_clean();

// ID enum
enum {
    ID_PL1,
    ID_PL2,
    ID_MAX
};

#endif

