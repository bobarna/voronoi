#include "sdl_init.h"

bool init(const int WINDOW_WIDTH, const int WINDOW_HEIGHT, SDL_Window **window, SDL_Renderer **renderer) {
// Initialization flag
    bool success = true;

// SDL initialization, opening the window
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("SDL can't be started: %s", SDL_GetError());
        success = false;
    }

// Creating the window, we'll be rendering to
    *window = SDL_CreateWindow("Voronoi Partitioner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                               WINDOW_HEIGHT, 0);
    if (*window == nullptr) {
        SDL_Log("Window couldn't be created: %s", SDL_GetError());
        success = false;
    }

// The render contained by the window
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_SOFTWARE);
    if (*renderer == nullptr) {
        SDL_Log("Renderer couldn't be created: %s", SDL_GetError());
        success = false;
    }

    return success;
}