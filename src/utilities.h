#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

inline float degrees_to_radians(float degrees) {
    return degrees * pi / 180.0;
}

/*returns a number in [0,1)*/
inline float random_float() {
    return std::rand() / (RAND_MAX + 1.0);
}

inline float random_float(float min, float max) {
    return min + (max-min)*random_float();
}

#include "colour.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

