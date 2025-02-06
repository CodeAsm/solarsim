#ifndef BODY_HPP
#define BODY_HPP

#include <glm/glm.hpp>

struct Body {
    double mass;
    glm::dvec3 position;
    glm::dvec3 velocity;
    glm::dvec3 acceleration;
};

#endif
