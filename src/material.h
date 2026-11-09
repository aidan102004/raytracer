#pragma once

#include "ray.h"
#include "hittable.h"
#include "colour.h"

class material {
public:
    virtual ~material() = default;

    virtual bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered) const {
        return false;
    }
};