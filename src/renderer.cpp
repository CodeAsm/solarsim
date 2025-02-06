#include "renderer.hpp"
#include "simulation.hpp"
#include <GLFW/glfw3.h>
#include <GL/gl.h>

void Renderer::init() {
    if (!glfwInit()) {
        // Initialization failed
    }
    // Additional initialization code
}

void Renderer::draw(const Simulation& sim) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (const auto& body : sim.getBodies()) { // Use the getBodies method
        glVertex3d(body.position.x, body.position.y, body.position.z);
    }
    glEnd();
    glfwSwapBuffers(glfwGetCurrentContext());
}
