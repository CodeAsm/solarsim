#include "body.hpp"

void updateAcceleration(Body& a, const Body& b, double G) {
    glm::dvec3 diff = b.position - a.position;
    double r2 = glm::dot(diff, diff) + 1e-9; // Vermijd /0
    double force = G * b.mass / r2;
    a.acceleration += force * glm::normalize(diff);
}
