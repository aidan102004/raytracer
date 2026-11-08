#pragma once

#include "hittable.h"

class sphere : public hittable {
private:
    point3 centre;
    float radius;
public:
    sphere(const point3& centre, float radius) : centre(centre), radius(std::fmax(0, radius)) {}

    bool hit(float ray_tmin, float ray_tmax, hit_record& rec, const ray& r) const override {
        vec3 oc = centre - r.origin(); //the vector from the ray origin to the sphere centre
        //define coefficients of the quadratic
        auto a = r.direction().length_squared(); 
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius*radius;
        auto discriminant = h*h - a*c; //solve the discriminant to find solutions
        if (discriminant < 0) 
            return false; //there are no solutions meaning the ray misses the sphere
        auto sqrtd = std::sqrt(discriminant);

        //find nearest root that lies in acceptable range
        auto root = (h - sqrtd) / a; //try nearest first
        if (root <= ray_tmin || root >= ray_tmax) {
            root = (h + sqrtd) / a; //try further root
            if (root <= ray_tmin || root >= ray_tmax) {
                return false;
            }
        }
        //record the hit
        rec.t = root;
        rec.p = r.at(rec.t); //solve for the 3D point
        vec3 outward_normal = (rec.p - centre) / radius;
        rec.set_face_normal(r, outward_normal); //sets normal
        return true;
    }   
};