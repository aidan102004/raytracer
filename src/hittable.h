#pragma once
#include "ray.h"

class hit_record {
public:
    point3 p; //the hit point in 3D space
    vec3 normal; //the surface normal
    float t; //how far along the ray hit occured
};

class hittable {
public:
    virtual ~hittable() = default;
    virtual bool hit(float ray_tmin, float ray_tmax, hit_record& rec, const ray& r) const = 0;
};