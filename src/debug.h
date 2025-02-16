#ifndef DEBUG_H
#define DEBUG_H

#include <SDL2/SDL.h>
#include "game.h"

int init_debug(void);
void render_debug_info(SDL_Renderer* renderer, GameState* state);
void cleanup_debug(void);

#endif
