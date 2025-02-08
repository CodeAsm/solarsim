#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <atomic>

extern std::atomic<bool> running;

struct Vector3D {
    double x, y, z;
};


#endif // GLOBALS_HPP