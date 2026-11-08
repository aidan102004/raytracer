#pragma once

#include "hittable.h"
#include <vector>

class hittable_list : public hittable {
public:
    std::vector<std::shared_ptr<hittable>> objects;

    hittable_list() {}
    hittable_list(std::shared_ptr<hittable> obj) {add(obj);}

    void clear() {objects.clear();}

    void add(std::shared_ptr<hittable> obj) {
        objects.push_back(obj);
    }

    bool hit(float ray_tmin, float ray_tmax, hit_record& rec, const ray& r) const override {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_tmax;

        for (const auto& obj : objects) {
            if (obj->hit(ray_tmin, closest_so_far, temp_rec, r)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_anything;
    }
};