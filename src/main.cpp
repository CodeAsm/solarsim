#include "simulation.hpp"
#include "renderer.hpp"
#include "body.hpp"
#include "globals.hpp"
#include <GLFW/glfw3.h>
#include <csignal>
#include <atomic>
#include <iostream>

std::atomic<bool> running(true);

void signalHandler(int signum) {
    running = false;
}

int main() {
    signal(SIGINT, signalHandler);

    Simulation sim;
    /*sim.addBody({"Sun", 1.989e30, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
    sim.addBody({"Earth", 5.972e24, {1.5e11, 0, 0}, {0, 29780, 0}, {0, 0, 0}});
    sim.addBody({"Moon", 7.348e22, {3.8e8, 0, 0}, {0, 1023, 0}, {0, 0, 0}});
    sim.addBody({"Mars", 6.39e23, {2.07e11, 0, 0}, {0, 24130, 0}, {0, 0, 0}});
    sim.addBody({"Jupiter", 1.898e27, {7.41e11, 0, 0}, {0, 13070, 0}, {0, 0, 0}});
    sim.addBody({"Saturn", 5.683e26, {1.35e12, 0, 0}, {0, 9670, 0}, {0, 0, 0}});
    sim.addBody({"Uranus", 8.681e25, {2.74e12, 0, 0}, {0, 6810, 0}, {0, 0, 0}});
    sim.addBody({"Neptune", 1.024e26, {4.45e12, 0, 0}, {0, 5430, 0}, {0, 0, 0}});
    sim.addBody({"Pluto", 1.309e22, {4.44e12, 0, 0}, {0, 6110, 0}, {0, 0, 0}});
    */
    double G = 6.67430e-11;
    sim.update(G);

    Renderer renderer;
    renderer.init(sim);

    while (!renderer.shouldClose() && running) {
        renderer.draw();
        glfwPollEvents();
    }

    renderer.shutdown();
    return 0;
}
