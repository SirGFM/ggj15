/**
 * @file src/background.c
 */

#include <GFraMe/GFraMe_object.h>
#include <GFraMe/GFraMe_tilemap.h>

#include "background.h"
#include "camera.h"
#include "global.h"

#define FLOOR_TILE 64
#define TILES_PER_LINE 15
#define TILE_WIDTH 8
#define TILE_HEIGHT 8

// Yep, this is stupid
static unsigned char map[] = {
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,
1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,
1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,
1,0,1,0,1,0,0,1,1,0,0,1,0,1,1,
1,0,1,0,1,0,1,0,0,1,0,1,0,1,1,
1,0,0,1,0,0,1,0,0,1,0,1,0,1,1,
1,0,0,1,0,0,0,1,1,0,0,1,1,1,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,1,1,1,1,1,1,1,1,1,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,1,1,1,1,1,1,1,1,1,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,
1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

#define NUM_LINES sizeof(map) / TILES_PER_LINE * TILE_HEIGHT
#define MAX_COL 2 * NUM_LINES

static int collidersLen;
static GFraMe_object colliders[MAX_COL];

static void bg_createColliders();

void bg_init() {
    int i;
    
    // Get all objects
    bg_createColliders();
    
    // Fix the tilemap position
    i = 0;
    while (i < sizeof(map)) {
        map[i] += FLOOR_TILE;
        i++;
    }
}

/**
 * Updates the current tilemap and its colliding objects according to the
 * camera position
 */
void bg_update() {
}

void bg_draw() {
    int i, offset, x, y;
    
    // Get the first tile position on screen
    y = -(cam_y % TILE_HEIGHT);
    // Get the first tile position
    offset = cam_y / TILE_HEIGHT * TILES_PER_LINE;
    
    i = 0;
    x = 0;
    while (1) {
        GFraMe_spriteset_draw
            (
             gl_sset8x8,
             map[offset + i],
             x,
             y,
             0 // flipped
            );
        
        x += TILE_WIDTH;
        if (x >= SCR_W) {
            x = 0;
            y += TILE_HEIGHT;
        }
        if (y - cam_y > SCR_H)
            break;
        i++;
    }
}

/**
 * Get the list of active colliders
 * 
 * @param list Return the list of active colliders
 * @return How many objects where returned
 */
int bg_getColliders(GFraMe_object **list) {
    int i, j;
    GFraMe_object *ret;
    
    ret = 0;
    
    i = -1;
    j = 0;
    while (++i < collidersLen) {
        // Find first valid collider
        if (!ret && colliders[i].y < cam_y)
            continue;
        // Assign it
        else if (!ret) {
            ret = &colliders[i];
            j = 1;
        }
        // Find every valid collider (i.e., in screen)
        else if (colliders[i].y < cam_y + SCR_H)
            j++;
        // Yay, stop!
        else
            break;
    }
    
    *list = ret;
    return j;
}

int bg_getHeight() {
    return sizeof(map) / TILES_PER_LINE * TILE_HEIGHT;
}

static void bg_createColliderObject(int pos, int firstTile, int lastTile) {
    int x, y, w, h;
    
    x = firstTile % TILES_PER_LINE * TILE_WIDTH;
    y = firstTile / TILES_PER_LINE * TILE_HEIGHT;
    
    w = (lastTile - firstTile + 1) * TILE_WIDTH;
    h = TILE_HEIGHT;
    
    GFraMe_object_clear(&colliders[pos]);
	GFraMe_object_set_x(&colliders[pos], x);
	GFraMe_object_set_y(&colliders[pos], y);
    
    GFraMe_hitbox_set
        (
         &colliders[pos].hitbox, 
         GFraMe_hitbox_upper_left,
         0, // x
         0, // y
         w, // w
         h  // h
        );
}

static void bg_createColliders() {
    int i, j, tilePos;
    
    i = -1;
    j = 0;
    tilePos = -1;
    while (++i < sizeof(map)) {
        if ((i % TILES_PER_LINE) == 0)
            continue;
        if ((i % TILES_PER_LINE) == TILES_PER_LINE - 1) {
            if (tilePos != -1) {
                bg_createColliderObject(j, tilePos, i - 1);
                
                // Go to next object position
                j++;
                tilePos = -1;
            }
            continue;
        }
        
        // If found first collideable on a line
        if (tilePos == -1 && map[i] == 1)
            tilePos = i;
        // If is creating a line and found a not collideable
        else if (tilePos != -1 && map[i] == 0) {
            bg_createColliderObject(j, tilePos, i - 1);
            
            // Go to next object position
            j++;
            tilePos = -1;
        }
    }
    
    collidersLen = j;
}

