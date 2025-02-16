#include "renderer.h"

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
    const int ball_radius = 10;
    for (int w = 0; w < ball_radius * 2; w++) {
        for (int h = 0; h < ball_radius * 2; h++) {
            int dx = ball_radius - w;
            int dy = ball_radius - h;
            if ((dx*dx + dy*dy) <= (ball_radius * ball_radius)) {
                SDL_RenderDrawPoint(renderer->renderer, 
                    state->ball_x + w - ball_radius, 
                    state->ball_y + h - ball_radius);
            }
        }
    }

#ifdef DEBUG
    render_debug_info(renderer->renderer, state);
#endif
    
    // Update screen
    SDL_RenderPresent(renderer->renderer);
}

void cleanup_renderer(Renderer* renderer) {
    SDL_DestroyRenderer(renderer->renderer);
    SDL_DestroyWindow(renderer->window);
}
