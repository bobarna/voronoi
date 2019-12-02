#include <iostream>
#include <vector>
#include "sdl_stuff.h"


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


int SDLWrapper::renderClear() {
    return SDL_RenderClear(renderer);
}

void SDLWrapper::fillVoronoi(Voronoi *voronoi) {
    if (voronoi->empty()) return;
    for (int x = 0; x < WINDOW_WIDTH; x++) {
        for (int y = 0; y < WINDOW_HEIGHT; y++) {
            Color curr = voronoi->getClosest(x, y);
            pixelRGBA(renderer, x, y, curr.r, curr.g, curr.b, curr.a);
        }
    }
}