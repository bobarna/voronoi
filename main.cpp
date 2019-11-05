#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

// Window dimension constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Starts up SDL and creates the window
bool init();

// The window we'll be rendering to
SDL_Window *window = nullptr;

// The renderer contained by the window
SDL_Renderer *renderer = nullptr;

bool init() {
    // Initialization flag
    bool success = true;

    // SDL initialization, opening the window
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("SDL can't be started: %s", SDL_GetError());
        success = false;
    }

    // Creating the window, we'll be rendering to
    window = SDL_CreateWindow("Voronoi Partitioner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                              WINDOW_HEIGHT, 0);
    if (window == NULL) {
        SDL_Log("Window couldn't be created: %s", SDL_GetError());
        success = false;
    }

    // The render contained by the window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Renderer couldn't be created: %s", SDL_GetError());
        success = false;
    }

    return success;
}

int main(int argc, char *argv[]) {

    // Initializing SDL
    // Exit if failed
    if (!init()) exit(1);

    SDL_RenderClear(renderer);

    // Event loop
    bool quit = false;


    bool start_line = true;
    int start_x = 0;
    int start_y = 0;

    // Event handler
    SDL_Event event;
    while (!quit) {
        // Fill up event with event.motion.x and event.motion.y
        SDL_WaitEvent(&event);
        switch (event.type) {
            /* Mouse click */
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    // Left button click
                    filledCircleRGBA(renderer, event.motion.x, event.motion.y, 5, 255, 0, 0, 255);
                    SDL_RenderPresent(renderer);
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    //Right button click
                    if (start_line) {
                        start_x = event.motion.x;
                        start_y = event.motion.y;
                        start_line = false;
                    } else {
                        lineRGBA(renderer, start_x, start_y, event.motion.x, event.motion.y, 255, 255, 255, 255);
                        SDL_RenderPresent(renderer);
                        start_line = true;
                    }
                }
                break;
                /* Closing the window */
            case SDL_QUIT:
                quit = true;
                break;
        }


    }

    // Close SDL
    SDL_Quit();

    return 0;
}