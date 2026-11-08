
#include "utilities.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"


colour ray_colour(const ray& r, const hittable& world) {
    //creates record and checks for hit, if hit assign color based on records normal
    hit_record rec;
    if(world.hit(interval(0, infinity), rec, r)) {
        return 0.5*(rec.normal + colour(1,1,1));
    }

    vec3 unit_direction = normalise(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0 - a)*colour(1.0,1.0,1.0) + a*colour(0.5,0.7,1.0);
}

int main()
{
    auto aspect_ratio = 16.0/9.0;
    int image_width = 400;

    int image_height = int(image_width/aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    //world
    hittable_list world;

    world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5f));
    world.add(std::make_shared<sphere>(point3(0,-100.5,-1), 100.0f));

    auto focal_len = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (float(image_width)/image_height);
    auto camera_centre = point3(0,0,0);

    auto viewport_u = vec3(viewport_width, 0, 0); //vector from left to right in x axis
    auto viewport_v = vec3(0, -viewport_height, 0); //vector from top to bottom in y axis

    //define pixel deltas
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = camera_centre - vec3(0, 0, focal_len) - viewport_u/2 - viewport_v/2; //moves forward by focal length to be at z = -1, moves left by half the vp and up by half the vp
    auto pixel00_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v); //sets top left pixel location so we can determine all other pixels locations from this


    //RENDER

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            auto pixel_centre = pixel00_location + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_dir = pixel_centre - camera_centre;
            ray r(camera_centre, ray_dir);

            colour pixel_colour = ray_colour(r, world);
            write_colour(std::cout, pixel_colour);
        }
    }
}




