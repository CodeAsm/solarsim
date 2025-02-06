#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "simulation.hpp"

class Renderer {
public:
    void init(Simulation& sim);
    void draw();
    void renderImGui();
    void shutdown();

private:
    Simulation* simulation;
};

#endif // RENDERER_HPP
