#include "Voronoi.h"


void Voronoi::color(SDL_Renderer *renderer, const int WINDOW_WIDTH, const int WINDOW_HEIGHT) {
    if (nodes.empty()) return;
    for (int x = 0; x < WINDOW_WIDTH; x++) {
        for (int y = 0; y < WINDOW_HEIGHT; y++) {
            Color curr = getClosest(x, y);
            pixelRGBA(renderer, x, y, curr.r, curr.g, curr.b, curr.a);
        }
    }
}

Color Voronoi::getClosest(int x, int y) {
    double min = nodes.back().dist(Coord(x, y));
    Color return_color = nodes.back().color;
    for (auto n: nodes) {
        if (n.dist(Coord(x, y)) < min)
            min = n.dist(Coord(x, y)), return_color = n.color;
    }
    return return_color;
}

void Voronoi::shuffleNodes(const int WINDOW_WIDTH, const int WINDOW_HEIGHT) {
    std::random_device rand;
    std::mt19937 rng(rand());
    std::uniform_int_distribution<std::mt19937::result_type> width(10, WINDOW_WIDTH - 10);
    std::uniform_int_distribution<std::mt19937::result_type> height(10, WINDOW_HEIGHT - 10);

    for (auto &currNode: nodes) {
        currNode.x = width(rng);
        currNode.y = height(rng);
    }

}