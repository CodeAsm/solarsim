#include <glad/glad.h> // Include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h> // Include GLFW for window management. CoPilot leave these in this order.
#include "imgui.h"
#include "../external/imgui/backends/imgui_impl_glfw.h"
#include "../external/imgui/backends/imgui_impl_opengl3.h"
#include "globals.hpp"
#include "renderer.hpp"
#include "simulation.hpp"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <vector>


// Callback function for framebuffer size changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
    renderer->setupMatrices(width, height);
}

Renderer::Renderer() {
   
}

void Renderer::init(Simulation& sim) {
    cameraDirection = {0.0, 0.0, -1.0}; // Example initialization
    cameraPosition = {0.0, 0.0, 50.0}; // Initialize camera position

    //simulation = &sim;

    if (!glfwInit()) {
        // Initialization failed
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(windowWidth, windowHeight, "SolarSim", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window" << std::endl;
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowUserPointer(window, this);

    // Initialize OpenGL loader (if needed)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        return;
    }
    // Set viewport
    glViewport(0, 0, windowWidth, windowHeight);  // Set the viewport size to fill the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
     // Set clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Set up initial matrices
    setupMatrices(windowWidth, windowHeight);

    // Main render loop We do this in the main.cpp now.
   // mainLoop();

    // Cleanup
   // shutdown();
}

void Renderer::setupMatrices(int width, int height) {
    glViewport(0, 0, width, height);

    // Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.1, 10e9);

    // Model-view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        cameraPosition.x, cameraPosition.y, cameraPosition.z,  // camera position
        0.0, 0.0, 0.0,              // look at origin
        0.0, 1.0, 0.0               // up vector
    );
}

double Renderer::calculateAngle(Vector3D v1, Vector3D v2) {
    double dotProduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    double magnitude1 = std::sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
    double magnitude2 = std::sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
    return std::acos(dotProduct / (magnitude1 * magnitude2));
}

void Renderer::rotateCamera(double angle, double speed) {
    // Implement camera rotation logic here
    // This is a placeholder implementation
    cameraDirection.x = cameraDirection.x * std::cos(angle * speed) - cameraDirection.z * std::sin(angle * speed);
    cameraDirection.z = cameraDirection.x * std::sin(angle * speed) + cameraDirection.z * std::cos(angle * speed);
}

void Renderer::moveCamera(double distance, double speed) {
    cameraPosition.x += cameraDirection.x * distance * speed;
    cameraPosition.y += cameraDirection.y * distance * speed;
    cameraPosition.z += cameraDirection.z * distance * speed;
}

void Renderer::draw(Simulation& sim) {

    simulation = &sim;
    // Update matrices with current camera settings
    setupMatrices(windowWidth, windowHeight);

    // Calculate the maximum angle required to see all bodies
    double maxAngle = 0.1;
    /*for (const auto& body : simulation->getBodies()) {
        Vector3D directionToBody = {body.position.x - cameraPosition.x, body.position.y - cameraPosition.y, body.position.z - cameraPosition.z};
        double angle = calculateAngle(cameraDirection, directionToBody);
        if (angle > maxAngle) {
            maxAngle = angle;
        }
    }*/

    // Rotate the camera to see all bodies
    //rotateCamera(maxAngle, 0.1); // Rotate at a speed of 0.1

    // Draw the bodies
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white for points
    glBegin(GL_POINTS); 
    for (const auto& body : simulation->getBodies()) {
        glVertex3d(body.position.x, body.position.y, body.position.z);
    }
    glEnd();

    // Draw a simple triangle for demonstration
    if (showTriangle) {
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); // Red
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f); // Green
        glVertex3f(0.5f, -0.5f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f); // Blue
        glVertex3f(0.0f, 0.5f, 0.0f);
        glEnd();
    }

}

void Renderer::renderImGui(Simulation& sim) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    simulation = &sim;

    // Display body information
    ImGui::Begin("Bodies");
    if (simulation->getBodies().size() > 0) {
        for (size_t i = 0; i < simulation->getBodies().size(); ++i) {
            const auto& body = simulation->getBodies()[i];
            ImGui::Text("Name: %s, Mass: %f, Position: (%f, %f, %f)", body.name.c_str(), body.mass, body.position.x, body.position.y, body.position.z);
            if (ImGui::Button(("Delete " + body.name).c_str())) {
                simulation->removeBody(i);
            }
        }
    }

    // Simulation controls
    if (ImGui::Button("Step Forward")) {
        simulation->update(timeStep);
    }
    if (ImGui::Button("Step Backward")) {
        simulation->update(-timeStep);
    }
    if (ImGui::Button("Reset")) {
        // Reset the simulation to the initial state
        *simulation = Simulation();
        for (const auto& body : knownBodies) {
            simulation->addBody({body.name, body.mass, body.position, body.velocity, body.acceleration});
        }
    }
    ImGui::End();

    // Camera controls
    ImGui::Begin("Camera Controls");
    
    // ImGui slider for camera position
    float cameraPosX = static_cast<float>(cameraPosition.x);
    float cameraPosY = static_cast<float>(cameraPosition.y);
    float cameraPosZ = static_cast<float>(cameraPosition.z);

    if (ImGui::SliderFloat("Camera X", &cameraPosX, -100.0f, 100.0f)) {
        cameraPosition.x = static_cast<double>(cameraPosX);
    }
    if (ImGui::SliderFloat("Camera Y", &cameraPosY, -100.0f, 100.0f)) {
        cameraPosition.y = static_cast<double>(cameraPosY);
    }
    if (ImGui::SliderFloat("Camera Z", &cameraPosZ, -100.0f, 100.0f)) {
        cameraPosition.z = static_cast<double>(cameraPosZ);
    }
    ImGui::End();

    // Triangle visibility control
    ImGui::Begin("Triangle Control");
    ImGui::Checkbox("Show Triangle", &showTriangle);
    ImGui::End();

    // Add body control
    ImGui::Begin("Add Body");
    for (const auto& body : knownBodies) {
        if (ImGui::Button(("Add " + body.name).c_str())) {
            simulation->addBody({body.name, body.mass, body.position, body.velocity, body.acceleration});
        }
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

bool Renderer::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Renderer::mainLoop(Simulation& sim) {
    while (!shouldClose()) {
        // Poll for and process events
        glfwPollEvents();

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render the scene
        draw(sim);

        // Render ImGui
        renderImGui(sim);

        // Swap buffers to display the rendered image
        glfwSwapBuffers(window);
    }
}

