#ifndef BODY_HPP
#define BODY_HPP

#include <string>
#include "globals.hpp"

class Body {
public:
    std::string name;
    double mass;
    Vector3D position;
    Vector3D velocity;
    Vector3D acceleration;

    Body(const std::string& name, double mass, const Vector3D& position, const Vector3D& velocity, const Vector3D& acceleration);

    const std::string& getName() const;
    double getMass() const;
    const Vector3D& getPosition() const;
    const Vector3D& getVelocity() const;
    const Vector3D& getAcceleration() const;

    void setPosition(const Vector3D& position);
    void setVelocity(const Vector3D& velocity);
    void setAcceleration(const Vector3D& acceleration);
};

#endif // BODY_HPP
