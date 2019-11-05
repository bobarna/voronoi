#ifndef NHF2_VORONOI_H
#define NHF2_VORONOI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <vector>
#include "Node.h"
#include <vector>

class Voronoi {
    std::vector<Node> nodes;

    Color getClosest(int x, int y);

public:
    void color(SDL_Renderer *renderer, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);

    void addNode(int x, int y) {
        nodes.emplace_back(Node(x, y));
        /*if(nodes.size() > 20) {
            nodes.erase(nodes.begin());
        }*/
    }

    void drawNodes(SDL_Renderer **renderer) {
        for (auto n: nodes)
            n.draw(*renderer);
    }
};


#endif //NHF2_VORONOI_H
