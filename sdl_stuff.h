#ifndef NHF2_SDL_INIT_H
#define NHF2_SDL_INIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <string>
#include "Voronoi.h"

class SDLWrapper {
    bool success = false;

    // The window we'll be rendering to
    SDL_Window *window = nullptr;
    // The renderer contained by the window
    SDL_Renderer *renderer = nullptr;
    TTF_Font *font;
    int WINDOW_WIDTH;
    int WINDOW_HEIGHT;

public:
    SDLWrapper(const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const char *FONT) {
        // Initialization flag
        success = true;

        this->WINDOW_WIDTH = WINDOW_WIDTH;
        this->WINDOW_HEIGHT = WINDOW_HEIGHT;

        // SDL initialization, opening the window
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            SDL_Log("SDL can't be started: %s", SDL_GetError());
            success = false;
        }

        // Creating the window, we'll be rendering to
        window = SDL_CreateWindow("Voronoi Partitioner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                  WINDOW_HEIGHT, 0);
        if (window == nullptr) {
            SDL_Log("Window couldn't be created: %s", SDL_GetError());
            success = false;
        }

        // The render contained by the window
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        if (renderer == nullptr) {
            SDL_Log("Renderer couldn't be created: %s", SDL_GetError());
            success = false;
        }

        TTF_Init();
        font = TTF_OpenFont(FONT, 24);
        if (font == nullptr) {
            SDL_Log("Font couldn't be loaded! %s\n", TTF_GetError());
            exit(1);
        }
    }

    ~SDLWrapper() {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;

        SDL_DestroyWindow(window);
        window = nullptr;

        TTF_CloseFont(font);
        font = nullptr;

        SDL_StopTextInput();

        SDL_Quit();
    }

    explicit operator bool() {
        return success;
    }

    int renderClear();

    void fillVoronoi(Voronoi *);

    SDL_Renderer *getRenderer() {
        return renderer;
    }

    TTF_Font *getFont() {
        return font;
    }
};


std::string getInput(SDL_Renderer *renderer, TTF_Font *font, const int WINDOW_HEIGHT, const int WINDOW_WIDTH);

void displayHelpWindow(SDL_Renderer *renderer, TTF_Font *font, const int WINDOW_HEIGHT, const int WINDOW_WIDTH);

#endif //NHF2_SDL_INIT_H
