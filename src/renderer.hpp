#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "simulation.hpp"
#include <GLFW/glfw3.h> // Include GLFW for window management

/* Renderer class
 * @brief   The Renderer class is responsible for rendering the simulation and handling user input.
 *        It uses GLFW for window management and OpenGL for rendering.
 *       It also uses ImGui for rendering the debug menu.
 */

class Renderer {
public:
    void init(Simulation& sim); 
    void draw();
    void renderImGui();
    void shutdown();
    bool shouldClose() const;
    void setupMatrices(int width, int height); 
    void mainLoop(); // Declare the mainLoop function

private:
    Simulation* simulation;
    GLFWwindow* window; // Store the window pointer
    double timeStep = 1.0; // Time step for simulation updates
    float cameraX = 0.0f; // Camera position
    float cameraY = 0.0f;
    float cameraZ = 50.0f;

    int windowWidth = 1280; //640;  // Window dimensions
    int windowHeight = 720; //480;
};

#endif // RENDERER_HPP
