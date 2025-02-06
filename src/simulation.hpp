#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include "body.hpp"

class Simulation {
public:
    std::vector<Body> bodies;
    double timeStep = 100; // Versnelling instelbaar

    void update(double G);
};

#endif
