#include "simulation.hpp"

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
       // body.velocity += body.acceleration * timeStep * 0.5;
       // body.position += body.velocity * timeStep;
       // body.velocity += body.acceleration * timeStep * 0.5;
    }
}

void Simulation::addBody(const Body& body) {
    bodies.push_back(body);
}

const std::vector<Body>& Simulation::getBodies() const {
    return bodies;
}

void Simulation::updateAcceleration(Body& body1, Body& body2, double G) {
    // Implement the logic to update the acceleration of body1 and body2 based on gravity
    // Example:
    // Vector3D direction = body2.position - body1.position;
    // double distance = direction.length();
    // double force = G * body1.mass * body2.mass / (distance * distance);
    // Vector3D acceleration = direction.normalized() * (force / body1.mass);
    // body1.acceleration += acceleration;
    // body2.acceleration -= acceleration;
}
