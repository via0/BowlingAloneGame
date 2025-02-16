#include "debug.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

static TTF_Font* debug_font = NULL;

// Add this function and call it after SDL init
int init_debug(void) {
    if (TTF_Init() == -1) {
        printf("TTF_Init failed: %s\n", TTF_GetError());
        return 0;
    }
    
    debug_font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", 14);
    if (!debug_font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return 0;
    }
    
    return 1;
}

// Add this cleanup function
void cleanup_debug(void) {
    if (debug_font) {
        TTF_CloseFont(debug_font);
    }
    TTF_Quit();
}

void render_debug_info(SDL_Renderer* renderer, GameState* state) {
    if (!debug_font) return;

    char debug_text[256];
    snprintf(debug_text, sizeof(debug_text), 
        "Ball Velocity X: %.2f\nBall Velocity Y: %.2f\nAngle: %.2f",
        state->ball_velocity_x,
        state->ball_velocity_y,
        0.0f  // Replace with actual angle when you add it
    );

    SDL_Color color = {255, 255, 255, 255};
    
    // Split and render each line
    char* line = strtok(debug_text, "\n");
    int y = 10;
    while (line != NULL) {
        SDL_Surface* text_surface = TTF_RenderText_Solid(debug_font, line, color);
        if (text_surface) {
            SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
            if (text_texture) {
                SDL_Rect dest = {10, y, text_surface->w, text_surface->h};
                SDL_RenderCopy(renderer, text_texture, NULL, &dest);
                SDL_DestroyTexture(text_texture);
            }
            SDL_FreeSurface(text_surface);
        }
        y += 20;
        line = strtok(NULL, "\n");
    }
}
