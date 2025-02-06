#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "simulation.hpp"

class Renderer {
public:
    void init();
    void draw(const Simulation& sim);
};

#endif
