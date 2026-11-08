#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

inline float degrees_to_radians(float degrees) {
    return degrees * pi / 180.0;
}

#include "colour.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

