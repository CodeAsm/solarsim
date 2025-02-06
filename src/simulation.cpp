#include "simulation.hpp"

void Simulation::update(double G) {
    // Reset acceleraties
    for (auto& body : bodies)
        body.acceleration = {0, 0, 0};

    // N-body zwaartekrachtberekening
    for (size_t i = 0; i < bodies.size(); i++) {
        for (size_t j = i + 1; j < bodies.size(); j++) {
            updateAcceleration(bodies[i], bodies[j], G);
            updateAcceleration(bodies[j], bodies[i], G);
        }
    }

    // Leapfrog integratie
    for (auto& body : bodies) {
        body.velocity += body.acceleration * timeStep * 0.5;
        body.position += body.velocity * timeStep;
        body.velocity += body.acceleration * timeStep * 0.5;
    }
}
