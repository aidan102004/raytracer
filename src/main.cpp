
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

    auto R = std::cos(pi/4);

    auto material_left  = std::make_shared<lambertian>(colour(0,0,1));
    auto material_right = std::make_shared<lambertian>(colour(1,0,0));

    world.add(std::make_shared<sphere>(point3(-R, 0, -1), R, material_left));
    world.add(std::make_shared<sphere>(point3( R, 0, -1), R, material_right));
    camera cam;
    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 800;
    cam.samples_per_pixel = 100;
    cam.max_recursion = 50;
    cam.vfov = 90;
    cam.render(world);
    

}




