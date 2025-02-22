#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

#define MAX_WALLS  10 // maximum number of walls a level can have

#define EPSILON    0.0001f // floating point zero
#define EPSILON_N -0.0001f // floating point negative 0

typedef struct {
  int ori_x;
  int ori_y;
  int width;
  int height;
  float angle_rad;

  bool defined;
} Wall;

typedef struct {
  float x;
  float y;
  float velocity_x;
  float velocity_y;
  Uint8 radius;
  float angle_rad;
} Ball;

typedef struct {
  Uint8 key_space_pressed;
  Uint8 key_angle_left_pressed;
  Uint8 key_angle_right_pressed;
  Uint8 key_walk_left_pressed;
  Uint8 key_walk_right_pressed;

  Wall walls[MAX_WALLS];
  Ball ball;
} GameState;

void init_game(GameState* state);
void update_game(GameState* state, float delta_time);
void handle_input(GameState* state, SDL_Event* event);

void ball_update(GameState* state);
void ball_updateVelocity(Ball* ball);
bool ball_isMoving(GameState* state);
bool ball_isCollidingWithWall(GameState* state, Wall* wall);

#endif
