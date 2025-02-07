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

// Callback function for framebuffer size changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
    renderer->setupMatrices(width, height);
}

void Renderer::init(Simulation& sim) {
    simulation = &sim;

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
    gluPerspective(45.0, (double)width / (double)height, 0.1, 1000.0);

    // Model-view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        cameraX, cameraY, cameraZ,  // camera position
        0.0, 0.0, 0.0,              // look at origin
        0.0, 1.0, 0.0               // up vector
    );
}

void Renderer::draw() {
    // Update matrices with current camera settings
    setupMatrices(windowWidth, windowHeight);

    // Draw the bodies
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white for points
    glBegin(GL_POINTS);
    for (const auto& body : simulation->getBodies()) {
        glVertex3d(body.position.x, body.position.y, body.position.z);
    }
    glEnd();

    // Draw a simple triangle for demonstration
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex3f(0.5f, -0.5f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();
}

void Renderer::renderImGui() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Display body information
    ImGui::Begin("Bodies");
    for (const auto& body : simulation->getBodies()) {
        ImGui::Text("Name: %s, Mass: %f, Position: (%f, %f, %f)", body.name.c_str(), body.mass, body.position.x, body.position.y, body.position.z);
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
        simulation->addBody({"Sun", 1.989e30, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
        simulation->addBody({"Earth", 5.972e24, {1.5e11, 0, 0}, {0, 29780, 0}, {0, 0, 0}});
        simulation->addBody({"Moon", 7.348e22, {3.8e8, 0, 0}, {0, 1023, 0}, {0, 0, 0}});
        simulation->addBody({"Mars", 6.39e23, {2.07e11, 0, 0}, {0, 24130, 0}, {0, 0, 0}});
        simulation->addBody({"Jupiter", 1.898e27, {7.41e11, 0, 0}, {0, 13070, 0}, {0, 0, 0}});
        simulation->addBody({"Saturn", 5.683e26, {1.35e12, 0, 0}, {0, 9670, 0}, {0, 0, 0}});
        simulation->addBody({"Uranus", 8.681e25, {2.74e12, 0, 0}, {0, 6810, 0}, {0, 0, 0}});
        simulation->addBody({"Neptune", 1.024e26, {4.45e12, 0, 0}, {0, 5430, 0}, {0, 0, 0}});
        simulation->addBody({"Pluto", 1.309e22, {4.44e12, 0, 0}, {0, 6110, 0}, {0, 0, 0}});
    }
    ImGui::End();

    // Camera controls
    ImGui::Begin("Camera Controls");
    ImGui::SliderFloat("Camera X", &cameraX, -100.0f, 100.0f);
    ImGui::SliderFloat("Camera Y", &cameraY, -100.0f, 100.0f);
    ImGui::SliderFloat("Camera Z", &cameraZ, 1.0f, 200.0f);
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

void Renderer::mainLoop() {
    while (!shouldClose()) {
        // Poll for and process events
        glfwPollEvents();

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render the scene
        draw();

        // Render ImGui
        renderImGui();

        // Swap buffers to display the rendered image
        glfwSwapBuffers(window);
    }
}
