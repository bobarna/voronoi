#ifndef NHF2_NODE_H
#define NHF2_NODE_H

#include <cstddef>
#include <cmath>
#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>

struct Coord {
    int x;
    int y;

    Coord(int x, int y) : x(x), y(y) {}

    double dist(Coord other) {
        return sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y));
    }
};

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    Color(unsigned char r,
          unsigned char g,
          unsigned char b,
          unsigned char a) :
            r(r), g(g), b(b), a(a) {}

    Color() {
        srand(time(nullptr));
        r = (rand() % 255);
        g = (rand() % 255);
        b = (rand() % 255);
        a = 255;
    }
};

struct Node : public Coord {
    Color color;
    size_t r = 5;

    Node(int x, int y) : Coord(x, y), color() { r = 5; }

    Node(int x, int y, int r) : Node(x, y) { this->r = r; }

    void draw(SDL_Renderer *renderer) {
        filledCircleRGBA(renderer, x, y, r, 100, 100, 100, 255);
    }
};


#endif //NHF2_NODE_H
