#include "renderer.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>

int init_renderer(Renderer* renderer) {
  renderer->screen_width = SCREEN_WIDTH;
  renderer->screen_height = SCREEN_HEIGHT;

  renderer->window = SDL_CreateWindow("Bowling Alone: A Love Story",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      renderer->screen_width, renderer->screen_height,
      SDL_WINDOW_SHOWN);

  if (!renderer->window) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return 0;
  }

  renderer->renderer = SDL_CreateRenderer(renderer->window, -1, 
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer->renderer) {
    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(renderer->window);
    return 0;
  }

  return 1;
}

void render_game(Renderer* renderer, GameState* state) {
  // Clear screen
  SDL_SetRenderDrawColor(renderer->renderer, 0x18, 0x18, 0x18, 0xFF);
  SDL_RenderClear(renderer->renderer);
  // Draw bowling alley (just a rectangle for now)
  SDL_SetRenderDrawColor(renderer->renderer, 0x8B, 0x45, 0x13, 0xFF);
  SDL_Rect alley = {100, 0, renderer->screen_width - 200, renderer->screen_height};
  SDL_RenderFillRect(renderer->renderer, &alley);

  // Draw ball
  SDL_SetRenderDrawColor(renderer->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  Uint8 ball_radius = state->ball.radius;
  for (int w = 0; w < ball_radius * 2; w++) {
    for (int h = 0; h < ball_radius * 2; h++) {
      int dx = ball_radius - w;
      int dy = ball_radius - h;
      if ((dx*dx + dy*dy) <= (ball_radius * ball_radius)) {
        SDL_RenderDrawPoint(renderer->renderer, 
            state->ball.x + w - ball_radius, 
            state->ball.y + h - ball_radius);
      }
    }
  }

  // Draw walls
  for (int i = 0; i < MAX_WALLS; i++) {
    if(state->walls[i].defined == 1) render_wall(renderer, &state->walls[i]);
  }

  // Draw pins
  for (int i = 0; i < NUM_PINS; i++) {
    if(state->pins[i].defined == 1) render_pin(renderer, &state->pins[i]);
  }

#ifdef DEBUG
  render_debug_info(renderer->renderer, state);
#endif

  // Update screen
  SDL_RenderPresent(renderer->renderer);
}

void render_ball(Renderer* renderer, Ball* ball) {
  // Draw ball
  SDL_SetRenderDrawColor(renderer->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  Uint8 ball_radius = ball->radius;
  for (int w = 0; w < ball_radius * 2; w++) {
    for (int h = 0; h < ball_radius * 2; h++) {
      int dx = ball_radius - w;
      int dy = ball_radius - h;
      if ((dx*dx + dy*dy) <= (ball_radius * ball_radius)) {
        SDL_RenderDrawPoint(renderer->renderer, 
            ball->x + w - ball_radius, 
            ball->y + h - ball_radius);
      }
    }
  }
}

void render_wall(Renderer* renderer, Wall* wall) {
  SDL_SetRenderDrawColor(renderer->renderer, 0x32, 0xa8, 0x52, 0xff);
  SDL_Rect wall_rect = {wall->ori_x, wall->ori_y, wall->width, wall->height};
  SDL_RenderFillRect(renderer->renderer, &wall_rect);
}

void render_pin(Renderer* renderer, Pin* pin) {
  if(pin->alive)
    render_live_pin(renderer, pin);
  else
    render_dead_pin(renderer, pin);
}

void render_live_pin(Renderer* renderer, Pin* pin) {
  SDL_SetRenderDrawColor(renderer->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  Uint8 pin_radius = pin->radius;
  for (int w = 0; w < pin_radius * 2; w++) {
    for (int h = 0; h < pin_radius * 2; h++) {
      int dx = pin_radius - w;
      int dy = pin_radius - h;
      if ((dx*dx + dy*dy) <= (pin_radius * pin_radius)) {
        SDL_RenderDrawPoint(renderer->renderer, 
            pin->x + w - pin_radius, 
            pin->y + h - pin_radius);
      }
    }
  }
}

void render_dead_pin(Renderer* renderer, Pin* pin) {
  // Generate texture for the rectangle
  SDL_Texture* rectTexture = SDL_CreateTexture(
      renderer->renderer,
      SDL_PIXELFORMAT_RGBA8888,
      SDL_TEXTUREACCESS_TARGET,
      PIN_RADIUS, PIN_HEIGHT
  );

  // Set the texture as the rendering target
  SDL_SetRenderTarget(renderer->renderer, rectTexture);

  // Fill the texture with the desired color
  SDL_SetRenderDrawColor(renderer->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer->renderer);

  // Reset rendering target to default (window)
  SDL_SetRenderTarget(renderer->renderer, NULL);

  // Define actual rectangle object
  SDL_Rect pin_rect = {pin->x - (pin->radius / 2),
                       pin->y - (pin->height),
                       pin->radius,
                       pin->height};

  // Define rotation point (bottom of rectangle)
  SDL_Point rotationPoint = {
    pin->radius / 2, // X center of sprite
    pin->height      // Y bottom of sprite
  };

  // Render the rectangle with rotation
  SDL_RenderCopyEx(
      renderer->renderer,
      rectTexture,
      NULL,
      &pin_rect,
      pin->angle_rad * -180.0f / M_PI, // rotation is clockwise bc SDL is insane
      &rotationPoint,
      SDL_FLIP_NONE
  );
}

void cleanup_renderer(Renderer* renderer) {
  SDL_DestroyRenderer(renderer->renderer);
  SDL_DestroyWindow(renderer->window);
}
