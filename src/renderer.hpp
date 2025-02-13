#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include <string>
#include "globals.hpp"
#include <GLFW/glfw3.h>
#include "simulation.hpp"

/* Renderer class
 * @brief   The Renderer class is responsible for rendering the simulation and handling user input.
 *        It uses GLFW for window management and OpenGL for rendering.
 *       It also uses ImGui for rendering the debug menu.
 */
class Renderer {
public:
    //Renderer(Simulation* sim, GLFWwindow* win);
    Renderer();
    void setupMatrices(int width, int height);
    void init(Simulation& sim); 
    void renderImGui(Simulation& sim);
    void shutdown();
    bool shouldClose() const;
    void mainLoop();
    void mainLoop(Simulation& sim);
    double calculateAngle(Vector3D v1, Vector3D v2);

private:
    //const Simulation& simulation; // Store a reference to the simulation
    Simulation* simulation;
    GLFWwindow* window;
    double timeStep = 1.0;
    Vector3D cameraDirection; // Declare cameraDirection as a member variable
    Vector3D cameraPosition; // Declare cameraPosition as a member variable
    

    int windowWidth = 1280;
    int windowHeight = 720;

    bool showTriangle = true;

    struct KnownBody {
        std::string name;
        double mass;
        Vector3D position;
        Vector3D velocity;
        Vector3D acceleration;
    };

    
    std::vector<KnownBody> knownBodies = {
        {"Sun", 1.989e30, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {"Mercury", 3.285e23, {5.79e10, 0, 0}, {0, 47360, 0}, {0, 0, 0}},
        {"Venus", 4.867e24, {1.082e11, 0, 0}, {0, 35020, 0}, {0, 0, 0}},
        {"Earth", 5.972e24, {1.5e11, 0, 0}, {0, 29780, 0}, {0, 0, 0}},
        {"Moon", 7.348e22, {1.5038e11, 0, 0}, {0, 30780, 0}, {0, 0, 0}},
        {"Mars", 6.39e23, {2.279e11, 0, 0}, {0, 24070, 0}, {0, 0, 0}},
        {"Jupiter", 1.898e27, {7.785e11, 0, 0}, {0, 13070, 0}, {0, 0, 0}},
        {"Saturn", 5.683e26, {1.433e12, 0, 0}, {0, 9680, 0}, {0, 0, 0}},
        {"Uranus", 8.681e25, {2.877e12, 0, 0}, {0, 6800, 0}, {0, 0, 0}},
        {"Neptune", 1.024e26, {4.503e12, 0, 0}, {0, 5430, 0}, {0, 0, 0}},
    };

    void rotateCamera(double angle, double speed);
    void moveCamera(double distance, double speed);
    void draw();
};

#endif // RENDERER_HPP
