#ifndef NHF2_SDL_INIT_H
#define NHF2_SDL_INIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <string>

// Starts up SDL and creates the window
bool
init(const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const char *FONT, SDL_Window **window, SDL_Renderer **renderer,
     TTF_Font **font);

void sdl_close(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font);

std::string getInput(SDL_Renderer *renderer, TTF_Font *font, const int WINDOW_HEIGHT, const int WINDOW_WIDTH);

void displayHelpWindow(SDL_Renderer *renderer, TTF_Font *font, const int WINDOW_HEIGHT, const int WINDOW_WIDTH);

#endif //NHF2_SDL_INIT_H
