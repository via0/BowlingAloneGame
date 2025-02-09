#include "game.h"

void init_game(GameState* state) {
    // Initialize ball in bottom center
    state->ball_x = (float) (SCREEN_WIDTH / 2);  // middle of screen
    state->ball_y = (float) (0.9 * SCREEN_HEIGHT);  // near bottom
    state->ball_velocity_x = 0.0f;
    state->ball_velocity_y = 0.0f;
}

void update_game(GameState* state, float delta_time) {
    // This is where you'll put your physics code!
    // For now, we'll just keep the ball static
}

void handle_input(GameState* state, SDL_Event* event) {
    // This is where you'll handle keyboard/mouse input
    // For launching the ball, setting angle, etc.
}
