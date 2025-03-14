#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

#define MAX_WALLS  10 // maximum number of walls a level can have
#define NUM_PINS   10 // 10 pins in a bowling game, of course!
#define NUM_FRAMES 10 // 10 frames in a game, of course!!

#define PIN_RADIUS 5
#define PIN_HEIGHT 10 // THAT'S QUITE BIG

#define BALL_RADIUS 10

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
  int x;
  int y;
  Uint8 radius;
  Uint8 height; // when it's knocked over, this is length of the pin
  bool alive;   // has this pin been defeated?
  bool defined; // should this pin be rendered at all?
} Pin;

typedef struct {
  Uint8 key_space_pressed;
  Uint8 key_angle_left_pressed;
  Uint8 key_angle_right_pressed;
  Uint8 key_walk_left_pressed;
  Uint8 key_walk_right_pressed;

  Wall walls[MAX_WALLS];
  Ball ball;
  Pin  pins[NUM_PINS];
} GameState;

void init_game(GameState* state);
void init_pins(GameState* state);
void update_game(GameState* state, float delta_time);
void handle_input(GameState* state, SDL_Event* event);

void ball_update(GameState* state);
void ball_updateVelocity(Ball* ball);
bool ball_isMoving(GameState* state);
bool ball_isCollidingWithWall(GameState* state, Wall* wall);

#endif
