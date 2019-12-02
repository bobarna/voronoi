#ifndef VORONOI_H
#define VORONOI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <vector>
#include "Node.h"
#include <vector>

class Voronoi {
    std::vector<Node> nodes;


    bool drawNodesOn = true;
    bool capNodes = true;

public:
    Color getClosest(int x, int y);

    void addNode(int x, int y) {
        nodes.emplace_back(Node(x, y));
        if (nodes.size() > 16 && capNodes) {
            nodes.erase(nodes.begin());
        }
    }

    void toggleDrawNodes() {
        drawNodesOn = !drawNodesOn;
    }

    void toggleCapNodes() {
        while (nodes.size() > 16)
            nodes.erase(nodes.begin());

        capNodes = !capNodes;
    }

    void drawNodes(SDL_Renderer *renderer) {
        if (!drawNodesOn) return;
        if (nodes.empty()) return;
        for (auto n: nodes)
            n.draw(renderer);
        SDL_RenderPresent(renderer);
    }

    void shuffleNodes(const int WINDOW_WIDTH, const int WINDOW_HEIGHT);

    void clear() {
        nodes.clear();
    }

    bool empty() {
        return nodes.empty();
    }
};


#endif
