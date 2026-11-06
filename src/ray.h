#pragma once

#include "vec3.h"

class ray {
public:
    ray() {}

    ray(const point3& origin, const vec3& direction) : orig(std::move(origin)), dir(std::move(direction)) {};

    const point3& origin() const {return orig;}
    const vec3& direction() const {return dir;}

    point3 at(float t) const {
        return orig + (t*dir);
    }

private:
    //follows formula P(t) = A + tb where P is a 3d point along a line. A is the ray origin point and b is the direction
    point3 orig;
    vec3 dir;
};