#include "body.hpp"

Body::Body(const std::string& name, double mass, const Vector3D& position, const Vector3D& velocity, const Vector3D& acceleration)
    : name(name), mass(mass), position(position), velocity(velocity), acceleration(acceleration) {}

const std::string& Body::getName() const {
    return name;
}

double Body::getMass() const {
    return mass;
}

const Vector3D& Body::getPosition() const {
    return position;
}

const Vector3D& Body::getVelocity() const {
    return velocity;
}

const Vector3D& Body::getAcceleration() const {
    return acceleration;
}

void Body::setPosition(const Vector3D& position) {
    this->position = position;
}

void Body::setVelocity(const Vector3D& velocity) {
    this->velocity = velocity;
}

void Body::setAcceleration(const Vector3D& acceleration) {
    this->acceleration = acceleration;
}
