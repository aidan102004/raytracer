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

class lambertian : public material {
private:
    colour albedo;
public:
    lambertian(const colour& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered) const override {
        auto scatter_dir = rec.normal + random_unit_vec();
        if (scatter_dir.near_zero()) scatter_dir = rec.normal; //check random vector isnt opposite from the normal
        scattered = ray(rec.p, scatter_dir);
        attenuation = albedo;
        return true;
    }
     
};

class metal : public material {
private:
    colour albedo;
    float fuzz;
public:
    metal(const colour& albedo, float fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}
    bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(r_in.direction(), rec.normal); //find reflected vector passing in direction of ray and normal of surface
        reflected = normalise(reflected) + (fuzz*random_unit_vec()); //add fuzz
        scattered = ray(rec.p, reflected); //assigns new reflected ray to output param
        attenuation = albedo; //assign attenuation output param
        return (dot(scattered.direction(), rec.normal) > 0); //determite if ray was absorbed into surface (negative dot product)
    }
};

class dielectric : public material {
private:
    float refractive_index;
public:
    dielectric(float refractive_index) : refractive_index(refractive_index) {}
    
   bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered) const override {
        attenuation = colour(1.0, 1.0, 1.0);
        float ri = rec.front_face ? (1.0/refractive_index) : refractive_index;
        vec3 unit_direction = normalise(r_in.direction());
        vec3 refracted = refract(unit_direction, rec.normal, ri);

        scattered = ray(rec.p, refracted);
        return true;
    }
};