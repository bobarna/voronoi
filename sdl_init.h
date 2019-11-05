#ifndef NHF2_SDL_INIT_H
#define NHF2_SDL_INIT_H

#include <SDL2/SDL.h>

// Starts up SDL and creates the window
bool init(const int WINDOW_WIDTH, const int WINDOW_HEIGHT, SDL_Window **window, SDL_Renderer **renderer);

#endif //NHF2_SDL_INIT_H
