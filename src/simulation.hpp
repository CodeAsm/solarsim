#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include "body.hpp"

class Simulation {
public:
    void update(double G);
    void addBody(const Body& body);
    const std::vector<Body>& getBodies() const;
    void removeBody(size_t index); // Add this method

private:
    void updateAcceleration(Body& body1, Body& body2, double G);

    std::vector<Body> bodies;
    double timeStep;
};

#endif // SIMULATION_HPP
