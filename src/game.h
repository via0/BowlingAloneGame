#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

#define EPSILON    0.0001f // floating point zero
#define EPSILON_N -0.0001f // floating point negative 0

typedef struct {
  float ball_x;
  float ball_y;
  float ball_velocity_x;
  float ball_velocity_y;

  Uint8 key_space_pressed;
  Uint8 key_angle_left_pressed;
  Uint8 key_angle_right_pressed;
  Uint8 key_walk_left_pressed;
  Uint8 key_walk_right_pressed;
} GameState;

void init_game(GameState* state);
void update_game(GameState* state, float delta_time);
void handle_input(GameState* state, SDL_Event* event);

void ball_update(GameState* state);
bool ball_isMoving(GameState* state);

#endif
