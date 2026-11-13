
#include "utilities.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"


int main()
{
    //world
    hittable_list world;

    auto material_ground = std::make_shared<lambertian>(colour(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<lambertian>(colour(0.1, 0.2, 0.5));
    auto material_left   = std::make_shared<dielectric>(1.50f);
    auto material_bubble = std::make_shared<dielectric>(1.00f / 1.50f);
    auto material_right  = std::make_shared<metal>(colour(0.8, 0.6, 0.2), 1.0f);

    world.add(std::make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0f, material_ground));
    world.add(std::make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5f, material_center));
    world.add(std::make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5f, material_left));
    world.add(std::make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.4f, material_bubble));
    world.add(std::make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5f, material_right));

    camera cam;
    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 800;
    cam.samples_per_pixel = 100;
    cam.max_recursion = 50;
    cam.vfov = 90;
    cam.look_from = point3(-2,2,1);
    cam.look_at   = point3(0,0,-1);
    cam.vup      = vec3(0,1,0);
    cam.render(world);
    

}




