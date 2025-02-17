#include "game.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <stdlib.h>

void init_game(GameState* state) {
  // Initialize ball in bottom center
  state->ball_x = (float) (0.5 * SCREEN_WIDTH);  // middle of screen
  state->ball_y = (float) (0.9 * SCREEN_HEIGHT);  // near bottom
  state->ball_velocity_x = 0.0f;
  state->ball_velocity_y = 0.0f;
}

void update_game(GameState* state, float delta_time) {
  // This is where you'll put your physics code!
  ball_update(state); // update ball position and state
}

void ball_update(GameState* state){
  if(!ball_isMoving(state) && state->key_space_pressed) {
    // fixme: ball velocity x, y should be scaled based on current angle
    state->ball_velocity_y = -10; // shoot up towards top of screen baby
  } else { // ball is moving
    state->ball_x += state->ball_velocity_x;
    state->ball_y += state->ball_velocity_y;
  }
}

bool ball_isMoving(GameState* state){
  return (((state->ball_velocity_x * state->ball_velocity_x) +
          (state->ball_velocity_y * state->ball_velocity_y))
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
