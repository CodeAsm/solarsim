#include "simulation.hpp"
#include "body.hpp" // Include the header file that defines the Body class
#include <cmath> // Include cmath for std::sqrt

void Simulation::update(double G) {
    // Reset accelerations
    for (auto& body : bodies)
        body.acceleration = {0, 0, 0};

    // N-body gravity calculation
    for (size_t i = 0; i < bodies.size(); i++) {
        for (size_t j = i + 1; j < bodies.size(); j++) {
            updateAcceleration(bodies[i], bodies[j], G);
            updateAcceleration(bodies[j], bodies[i], G);
        }
    }

    // Leapfrog integration
    for (auto& body : bodies) {
        body.velocity.x += body.acceleration.x * timeStep * 0.5;
        body.velocity.y += body.acceleration.y * timeStep * 0.5;
        body.velocity.z += body.acceleration.z * timeStep * 0.5;

        body.position.x += body.velocity.x * timeStep;
        body.position.y += body.velocity.y * timeStep;
        body.position.z += body.velocity.z * timeStep;

        body.velocity.x += body.acceleration.x * timeStep * 0.5;
        body.velocity.y += body.acceleration.y * timeStep * 0.5;
        body.velocity.z += body.acceleration.z * timeStep * 0.5;
    }
}

// Implement the addBody method to add a body to the simulation
void Simulation::addBody(const Body& body) {
    bodies.push_back(body);
}

const std::vector<Body>& Simulation::getBodies() const {
    return bodies;
}

// Implement the removeBody method to remove a body from the simulation
void Simulation::removeBody(size_t index) {
    if (index < bodies.size()) {
        bodies.erase(bodies.begin() + index);
    }
}
void Simulation::updateAcceleration(Body& body1, Body& body2, double G) {
    double dx = body2.position.x - body1.position.x;
    double dy = body2.position.y - body1.position.y;
    double dz = body2.position.z - body1.position.z;
    double distSq = dx * dx + dy * dy + dz * dz;
    if (distSq < 1e-12) return;

    double dist = std::sqrt(distSq);
    double force = G * body1.mass * body2.mass / distSq;
    double dirX = dx / dist;
    double dirY = dy / dist;
    double dirZ = dz / dist;

    double accel1 = force / body1.mass;
    body1.acceleration.x += dirX * accel1;
    body1.acceleration.y += dirY * accel1;
    body1.acceleration.z += dirZ * accel1;

    double accel2 = force / body2.mass;
    body2.acceleration.x -= dirX * accel2;
    body2.acceleration.y -= dirY * accel2;
    body2.acceleration.z -= dirZ * accel2;
}
