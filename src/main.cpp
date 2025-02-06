#include "simulation.hpp"
#include "body.hpp"
#include <GLFW/glfw3.h>
#include "renderer.hpp"

int main() {
    Simulation sim;

    sim.addBody({1.989e30, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
    sim.addBody({5.972e24, {1.5e11, 0, 0}, {0, 29780, 0}, {0, 0, 0}});

    Renderer renderer;
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Solar Simulation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    renderer.init();
    
    while (!glfwWindowShouldClose(window)) {
        double G = 6.67430e-11;
        sim.update(G);
        renderer.draw(sim);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
