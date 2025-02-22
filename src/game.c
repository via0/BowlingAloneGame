#include "game.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <stdlib.h>
#include <math.h>

void init_game(GameState* state) {
  // Initialize ball in bottom center
  state->ball.x = (float) (0.5 * SCREEN_WIDTH);  // middle of screen
  state->ball.y = (float) (0.9 * SCREEN_HEIGHT);  // near bottom
  state->ball.velocity_x = 0.0f;
  state->ball.velocity_y = 0.0f;
  state->ball.angle_rad  = 0.0f;
  state->ball.radius     = 10;

  // Initialize wall on left and right side of alley
  state->walls[0].ori_x   = 0.2 * SCREEN_WIDTH;
  state->walls[0].ori_y   = 0;
  state->walls[0].width   = 10;
  state->walls[0].height  = SCREEN_HEIGHT;
  state->walls[0].defined = 1;

  state->walls[1].ori_x   = (0.8 * SCREEN_WIDTH) - 10;
  state->walls[1].ori_y   = 0;
  state->walls[1].width   = 10;
  state->walls[1].height  = SCREEN_HEIGHT;
  state->walls[1].defined = 1;


}

void update_game(GameState* state, float delta_time) {
  // This is where you'll put your physics code!
  ball_update(state); // update ball position based on current velocity and user input
  for (Uint8 i = 0; i < MAX_WALLS; i++){
    if(state->walls[i].defined && ball_isCollidingWithWall(state, &state->walls[i])) {
      // TODO: angle of incidence, angle of reflection calculation
      state->ball.velocity_x = 0;
      state->ball.velocity_y = 0;
    }
  }
}

// TODO: this function is doing too much, updating ball based on velocity
// should be diffeent from updating ball based on walking and both should
// be different from updating ball velocity itself
void ball_update(GameState* state){
  if(!ball_isMoving(state)){
    if(state->key_space_pressed){ // launch ball based on current angle
      state->ball.velocity_y = -5.0f * cos(state->ball.angle_rad);
      state->ball.velocity_x = -5.0f * sin(state->ball.angle_rad);
    } else {
      if(state->key_walk_left_pressed)   state->ball.x -= 5;
      if(state->key_walk_right_pressed)  state->ball.x += 5;
      if(state->key_angle_left_pressed)  state->ball.angle_rad += (M_PI * 0.05f);
      if(state->key_angle_right_pressed) state->ball.angle_rad -= (M_PI * 0.05f);
    }
  } else {
    state->ball.x += state->ball.velocity_x;
    state->ball.y += state->ball.velocity_y;
  }
}

bool ball_isMoving(GameState* state){
  return (((state->ball.velocity_x * state->ball.velocity_x) +
          (state->ball.velocity_y * state->ball.velocity_y))
          > (EPSILON * EPSILON));
}

void handle_input(GameState* state, SDL_Event* event) {
  // This is where you'll handle keyboard/mouse input
  // For launching the ball, setting angle, etc.

  if (event->type == SDL_KEYDOWN) {
    SDL_Event quit_event;

    switch (event->key.keysym.sym) {
      case SDLK_ESCAPE:
        quit_event.type = SDL_QUIT;
        SDL_PushEvent(&quit_event);
        break;

      case SDLK_SPACE:
        state->key_space_pressed = 1;
        break;
      case SDLK_LEFT:
        state->key_angle_left_pressed = 1;
        break;
      case SDLK_RIGHT:
        state->key_angle_right_pressed = 1;
        break;
      case SDLK_a:
        state->key_walk_left_pressed = 1;
        break;
      case SDLK_d:
        state->key_walk_right_pressed = 1;
        break;
    }
  }

  if (event->type == SDL_KEYUP) {
    switch (event->key.keysym.sym) {
      case SDLK_SPACE:
        state->key_space_pressed = 0;
        break;
      case SDLK_LEFT:
        state->key_angle_left_pressed = 0;
        break;
      case SDLK_RIGHT:
        state->key_angle_right_pressed = 0;
        break;
      case SDLK_a:
        state->key_walk_left_pressed = 0;
        break;
      case SDLK_d:
        state->key_walk_right_pressed = 0;
        break;
    }
  }
}


// largely borrowed from jeffreythompson.org/collision-detection/circle-rect.php
bool ball_isCollidingWithWall(GameState* state, Wall *wall) {
  // determine the point on the rectangle (wall) closest to the center of the ball
  float testX;
  float testY;

  if (state->ball.x < wall->ori_x)
    testX = wall->ori_x;                // center of ball is to the left of the rectangle
  else if (state->ball.x > wall->ori_x + wall->width)
    testX = wall->ori_x + wall->width;  // center of ball is to the right of the rectangle
  else
    testX = state->ball.x;              // center of ball lies between the left and right coordinates of the rectangle

  if (state->ball.y < wall->ori_y)
    testY = wall->ori_y;                // center of ball is above the rectangle
  else if (state->ball.y > wall->ori_y + wall->height)
    testY = wall->ori_y + wall->height; // center of ball is below the rectangle
  else
    testY = state->ball.y;              // center of ball lies between the top and bottom coordinates of the rectangle

  float distX = state->ball.x - testX;
  float distY = state->ball.y - testY;

  printf("distX: %f\ndistY: %f\nradius: %f", distX, distY, (float)state->ball.radius);
  return ((distX * distX) + (distY * distY)) <= (state->ball.radius * state->ball.radius);
}
