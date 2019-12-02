#include "Voronoi.h"

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
        currNode.pos.x = width(rng);
        currNode.pos.y = height(rng);
    }

}