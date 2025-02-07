#include <glad/glad.h> // Include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h> // Include GLFW for window management. CoPilot leave these in this order.
#include "imgui.h"
#include "../external/imgui/backends/imgui_impl_glfw.h"
#include "../external/imgui/backends/imgui_impl_opengl3.h"
#include "globals.hpp"
#include "renderer.hpp"
#include "simulation.hpp"
#include <iostream>

// Callback function for framebuffer size changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Renderer::init(Simulation& sim) {
    simulation = &sim;

    if (!glfwInit()) {
        // Initialization failed
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "SolarSim", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window" << std::endl;
        return;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // GLAD initialization failed
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // Set viewport
    glViewport(0, 0, 640, 480);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Main render loop
    while (!glfwWindowShouldClose(window) && running) {
        // Input
        glfwPollEvents();

        // Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        draw();

        // Render ImGui
        renderImGui();

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    shutdown();
}

void Renderer::draw() {
    glBegin(GL_POINTS);
    for (const auto& body : simulation->getBodies()) {
        glVertex3d(body.position.x, body.position.y, body.position.z);
    }
    glEnd();
}

void Renderer::renderImGui() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Debug Menu");
    ImGui::Text("Bodies:");
    for (const auto& body : simulation->getBodies()) {
        ImGui::Text("Name: %s, Mass: %f, Position: (%f, %f, %f)", body.name.c_str(), body.mass, body.position.x, body.position.y, body.position.z);
    }

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
