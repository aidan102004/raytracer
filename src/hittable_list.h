#pragma once

#include "hittable.h"
#include <vector>

class hittable_list : public hittable {
public:
    std::vector<std::shared_ptr<hittable>> objects; //list of hittable objects in world

    hittable_list() {}
    hittable_list(std::shared_ptr<hittable> obj) {add(obj);} //constructor adds an obj to the list

    void clear() {objects.clear();}

    void add(std::shared_ptr<hittable> obj) {
        objects.push_back(obj);
    }

    bool hit(interval ray_t, hit_record& rec, const ray& r) const override {
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        //loop through objects and return true if we hit anything 
        for (const auto& obj : objects) {
            if (obj->hit(interval(ray_t.min, closest_so_far), rec, r)) {
                //if we hit assign rec
                hit_anything = true;
                closest_so_far = rec.t;
            }
        }
        return hit_anything;
    }
};