#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "sdl_stuff.h"
#include "Voronoi.h"

int main(int argc, char *argv[]) {

    // Window dimension constants
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const char *FONT = "LiberationSerif-Regular.ttf";

    // Initializing SDL
    SDLWrapper sdl = SDLWrapper(WINDOW_WIDTH, WINDOW_HEIGHT, FONT);
    // Exit if failed
    if (!(bool) sdl) exit(1);

    sdl.renderClear();

    // Event loop
    bool quit = false;

    std::string commandText = "";

    Voronoi voronoi;

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
                    // Add click position to the list of nodes
                    voronoi.addNode(event.motion.x, event.motion.y);
                    // Draw everything
                    sdl.fillVoronoi(&voronoi);
                    voronoi.drawNodes(sdl.getRenderer());
                    SDL_RenderPresent(sdl.getRenderer());
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    //Right button click
                }
                break;
            case SDL_TEXTINPUT:
                //Lenyomott egy gombot
                if (event.text.text[0] == ':') {
                    // getInput returns the string entered into the console appearing at the bottom of the window
                    commandText = getInput(sdl.getRenderer(), sdl.getFont(), WINDOW_HEIGHT, WINDOW_WIDTH);
                    // Let's redraw, so the console closes
                    sdl.fillVoronoi(&voronoi);
                    voronoi.drawNodes(sdl.getRenderer());
                    SDL_RenderPresent(sdl.getRenderer());
                    // A command was typed in, let's act on it!
                    // Let's separate the command
                    std::string command = commandText.substr(0, commandText.find(' '));
                    if (commandText == "save") {
                        // Save a screenshot of the voronoi art we just created
                        int format = SDL_PIXELFORMAT_ARGB8888;
                        SDL_Surface *out_surface = SDL_CreateRGBSurfaceWithFormat(0, WINDOW_WIDTH, WINDOW_HEIGHT, 32,
                                                                                  format);
                        SDL_RenderReadPixels(sdl.getRenderer(), NULL, format, out_surface->pixels,
                                             out_surface->pitch);

                        SDL_SaveBMP(out_surface, "output.bmp");
                        SDL_FreeSurface(out_surface);
                        std::cout << "screenshot saved successfully " << std::endl;
                    } else if ((commandText == "nodes") || (commandText == "seeds") || (commandText == "sites")) {
                        //Toggle the display of nodes
                        voronoi.toggleDrawNodes();
                        sdl.fillVoronoi(&voronoi);
                        voronoi.drawNodes(sdl.getRenderer());
                    } else if (commandText == "cap") {
                        // Toggle capping the nodes at 16
                        voronoi.toggleCapNodes();
                        sdl.fillVoronoi(&voronoi);
                        voronoi.drawNodes(sdl.getRenderer());
                    } else if (commandText == "shuffle") {
                        voronoi.shuffleNodes(WINDOW_WIDTH, WINDOW_HEIGHT);
                        std::cout << "shuffled" << std::endl;
                        sdl.fillVoronoi(&voronoi);
                        voronoi.drawNodes(sdl.getRenderer());

                    } else if (commandText == "clear") {
                        voronoi.clear();
                        SDL_RenderClear(sdl.getRenderer());
                        SDL_RenderPresent(sdl.getRenderer());
                    } else if (commandText == "help") {
                        // Display help window
                        displayHelpWindow(sdl.getRenderer(), sdl.getFont(), WINDOW_HEIGHT, WINDOW_WIDTH);
                    } else {
                        std::cout << "Unknown command " << std::endl;
                    }
                }
                break;
            case SDL_QUIT:
                /* Closing the window */
                quit = true;
                break;
        }
    }

    // SDLWrapper closes SDL automatically

    return 0;
}