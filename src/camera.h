#pragma once
#include "hittable.h"
#include "colour.h"
#include "ray.h"
class camera {
public:
    float aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10; //count for random samples per pixel

    void render(const hittable& h) {
        initialise();
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        for (int j = 0; j < image_height; j++) {
            for (int i = 0; i < image_width; i++) {
                colour pixel_colour(0,0,0); //we increment this vec3 with the pixel samples 
                //loop over number of samples we use
                for (size_t samp = 0; samp < samples_per_pixel; samp++) {
                    ray r = get_ray(i,j); //gets a random point in the pixel (i,j) returns a ray to that point
                    pixel_colour += ray_colour(r, h); //adds up all the samples
                }
                write_colour(std::cout, pixel_samples_scale * pixel_colour); //average
            }
        }
    }

private:
    int image_height;
    float pixel_samples_scale; //colour scale factor for a sum of pixel samples
    point3 centre;
    point3 pixel00_location;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    void initialise() {
        image_height = int(image_width/aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;
        pixel_samples_scale = 1.0/samples_per_pixel;

        auto focal_len = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (float(image_width)/image_height);
        centre = point3(0,0,0);

        auto viewport_u = vec3(viewport_width, 0, 0); //vector from left to right in x axis
        auto viewport_v = vec3(0, -viewport_height, 0); //vector from top to bottom in y axis

        //define pixel deltas
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        auto viewport_upper_left = centre - vec3(0, 0, focal_len) - viewport_u/2 - viewport_v/2; //moves forward by focal length to be at z = -1, moves left by half the vp and up by half the vp
        pixel00_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v); //sets top left pixel location so we can determine all other pixels locations from this
    }

    /*construct a camera ray originating from the origin and directed at a randomly sampled point around the pixel location (i,j)*/
    ray get_ray(int i, int j) const {
        auto offset = sample_pixel(); //x and y each in [-0.5, 0.5]
        auto pixel_sample = pixel00_location + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v); //get the random sampled point within that pixels bounds

        auto ray_origin = centre;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    /*get a sample vector offset*/
    vec3 sample_pixel() const {
        //random_float() gives us a number in [0,1) so substracting 0.5 gives us [-0.5,0.5)
        //therefore we get a pixel offset that can give us some random position within a pixels unit size of 1
        return vec3(random_float() - 0.5, random_float() - 0.5, 0);
    }

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
};