#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <vector>

#include "Node.h"
#include "sdl_init.h"
#include "Voronoi.h"

int main(int argc, char *argv[]) {

    // Window dimension constants
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    // The window we'll be rendering to
    SDL_Window *window = nullptr;

    // The renderer contained by the window
    SDL_Renderer *renderer = nullptr;

    // Initializing SDL
    bool success = init(WINDOW_WIDTH, WINDOW_HEIGHT, &window, &renderer);
    // Exit if failed
    if (!success) exit(1);

    SDL_RenderClear(renderer);

    // Event loop
    bool quit = false;

    // For testing lines
    bool start_line = true;
    int start_x = 0;
    int start_y = 0;

    Voronoi voronoi;
    std::vector<Node> nodes;

    // Event handler
    SDL_Event event;
    while (!quit) {
        // Fill up event with event.motion.x and event.motion.y
        SDL_WaitEvent(&event);
        switch (event.type) {
            /* Mouse click */
            case SDL_MOUSEBUTTONDOWN:
                // Left button click
                if (event.button.button == SDL_BUTTON_LEFT) {
                    // Add click position to the list of nodes
                    voronoi.addNode(event.motion.x, event.motion.y);
                    // Draw everything
                    voronoi.color(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
                    voronoi.drawNodes(&renderer);
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