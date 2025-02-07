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

    bool showTriangle = true; // Control triangle visibility

    struct KnownBody {
        std::string name;
        double mass;
        Vector3D position;
        Vector3D velocity;
        Vector3D acceleration;
};

    std::vector<KnownBody> knownBodies = {
        {"Sun", 1.989e30, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {"Earth", 5.972e24, {1.5e11, 0, 0}, {0, 29780, 0}, {0, 0, 0}},
        {"Moon", 7.348e22, {3.8e8, 0, 0}, {0, 1023, 0}, {0, 0, 0}},
        {"Mars", 6.39e23, {2.07e11, 0, 0}, {0, 24130, 0}, {0, 0, 0}},
        {"Jupiter", 1.898e27, {7.41e11, 0, 0}, {0, 13070, 0}, {0, 0, 0}},
        {"Saturn", 5.683e26, {1.35e12, 0, 0}, {0, 9670, 0}, {0, 0, 0}},
        {"Uranus", 8.681e25, {2.74e12, 0, 0}, {0, 6810, 0}, {0, 0, 0}},
        {"Neptune", 1.024e26, {4.45e12, 0, 0}, {0, 5430, 0}, {0, 0, 0}},
        {"Pluto", 1.309e22, {4.44e12, 0, 0}, {0, 6110, 0}, {0, 0, 0}}
    };
};
#endif // RENDERER_HPP