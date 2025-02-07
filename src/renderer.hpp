#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "simulation.hpp"
#include <GLFW/glfw3.h> // Include GLFW for window management

class Renderer {
public:
    void init(Simulation& sim);
    void draw();
    void renderImGui();
    void shutdown();
    bool shouldClose() const; // Add this method

private:
    Simulation* simulation;
    GLFWwindow* window; // Store the window pointer
    double timeStep = 1.0; // Time step for simulation updates
};

#endif // RENDERER_HPP
