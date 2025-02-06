#include "simulation.hpp"
#include "renderer.hpp"
#include <GLFW/glfw3.h>

int main() {
    Simulation sim;
    Renderer renderer;

    // Startwaarden: Zon & planeten
    sim.bodies.push_back({1.989e30, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
    sim.bodies.push_back({5.972e24, {1.5e11, 0, 0}, {0, 29780, 0}, {0, 0, 0}});

    renderer.init();
    
    while (!glfwWindowShouldClose(glfwGetCurrentContext())) {
        sim.update(6.67430e-11);
        renderer.draw(sim);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
