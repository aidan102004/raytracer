#pragma once


class hit_record {
public:
    point3 p; //the hit point in 3D space
    vec3 normal; //the surface normal
    float t; //how far along the ray hit occured
    bool front_face;

    /*sets normal whether ray is from inside or outside of hittable*/
    void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = (front_face) ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual ~hittable() = default;
    virtual bool hit(interval ray_t, hit_record& rec, const ray& r) const = 0;
};