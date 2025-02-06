#ifndef BODY_HPP
#define BODY_HPP

#include <string>
#include <array>

struct Vector3D {
    double x, y, z;
};

struct Body {
    std::string name;
    double mass;
    Vector3D position;
    Vector3D velocity;
    Vector3D acceleration;
};

#endif // BODY_HPP
