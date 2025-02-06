#include "renderer.hpp"
#include <GLFW/glfw3.h>

void Renderer::init() {
    glfwInit();
    // OpenGL setup...
}

void Renderer::draw(const Simulation& sim) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (const auto& body : sim.bodies) {
        glVertex3d(body.position.x, body.position.y, body.position.z);
    }
    glEnd();
    glfwSwapBuffers(glfwGetCurrentContext());
}
