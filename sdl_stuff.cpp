#include <iostream>
#include <vector>
#include "sdl_stuff.h"


bool
init(const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const char *FONT, SDL_Window **window, SDL_Renderer **renderer,
     TTF_Font **font) {
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

    TTF_Init();
    *font = TTF_OpenFont(FONT, 24);
    if (*font == nullptr) {
        SDL_Log("Font couldn't be loaded! %s\n", TTF_GetError());
        exit(1);
    }

    return success;
}

void sdl_close(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font) {
    SDL_DestroyRenderer(*renderer);
    *renderer = nullptr;

    SDL_DestroyWindow(*window);
    *window = nullptr;

    TTF_CloseFont(*font);
    *font = nullptr;

    SDL_StopTextInput();

    SDL_Quit();
}


std::string getInput(SDL_Renderer *renderer, TTF_Font *font, const int WINDOW_HEIGHT, const int WINDOW_WIDTH) {
    std::string commandText = "";
    SDL_Event event;

    while (true) {
        boxRGBA(renderer, 0, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT - 40, 0x55, 0x55, 0x55, 0xFF);
        SDL_Color White = {255, 255, 255};
        SDL_Surface *textSurface = TTF_RenderUTF8_Blended(font, commandText.c_str(), White);
        SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);
        int w = 0;
        int h = 0;
        // Calculating the size of the font
        TTF_SizeText(font, commandText.c_str(), &w, &h);
        SDL_Rect dest = {5, WINDOW_HEIGHT - 35, w, h};
        SDL_RenderCopy(renderer, text, NULL, &dest);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(text);
        SDL_RenderPresent(renderer);
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    // Backspace was pressed
                    if (commandText.size() > 1) {
                        commandText.pop_back();
                    } else {
                        commandText = "esc";
                        return commandText;
                    }
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    return commandText;
                } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    commandText = "esc";
                    return commandText;
                } else {
                    commandText += (char) event.key.keysym.sym;
                }
                break;
            case SDL_QUIT:
                SDL_PushEvent(&event);
                break;
        }
    }
}

void displayHelpWindow(SDL_Renderer *renderer, TTF_Font *font, const int WINDOW_HEIGHT, const int WINDOW_WIDTH) {
    //Window covering entire window
    boxRGBA(renderer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0x55, 0x55, 0x55, 0xFF);

    SDL_Color White = {255, 255, 255};

    std::vector<std::string> helpWindowLines;
    helpWindowLines.emplace_back("Available commands:");
    helpWindowLines.emplace_back("help - you are viewing this right now");
    helpWindowLines.emplace_back("save - saves the Voronoi diagram as output.bmp");
    helpWindowLines.emplace_back("nodes | seeds | sites - toggle display");
    helpWindowLines.emplace_back("cap - toggle capping the nr. of nodes at 16 on/off");
    helpWindowLines.emplace_back("shuffle - shuffle the position of the nodes");
    helpWindowLines.emplace_back("clear - clear all the nodes");

    int nr = 0;
    for (auto currLine: helpWindowLines) {
        SDL_Surface *textSurface = TTF_RenderUTF8_Blended(font, currLine.c_str(), White);
        SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);
        int w = 0;
        int h = 0;
        // Calculating the size of the font
        TTF_SizeText(font, currLine.c_str(), &w, &h);
        SDL_Rect dest = {5, 10 + (nr++) * h, w, h};
        SDL_RenderCopy(renderer, text, NULL, &dest);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(text);
    }


    SDL_RenderPresent(renderer);
}