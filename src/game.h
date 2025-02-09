#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

typedef struct {
  float ball_x;
  float ball_y;
  float ball_velocity_x;
  float ball_velocity_y;
} GameState;

void init_game(GameState* state);
void update_game(GameState* state, float delta_time);
void handle_input(GameState* state, SDL_Event* event);

#endif
