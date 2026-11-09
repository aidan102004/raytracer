#pragma once

#include "interval.h"
#include "vec3.h"


using colour = vec3;

/*gamma correction*/
inline float linear_to_gamma(float linear_comp) {
    if (linear_comp > 0) {
        return std::sqrt(linear_comp);
    }
    return 0;
}

void write_colour(std::ostream& out, const colour& pixel_colour) {
    auto r = pixel_colour.x();
    auto g = pixel_colour.y();
    auto b = pixel_colour.z();

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    //transalte [0,1] component values to the byte range [0,255]
    static const interval intensity(0.000, 0.999); //saftey net for clamping
    int r_byte = int(256 * intensity.clamp(r));
    int g_byte = int(256 * intensity.clamp(g));
    int b_byte = int(256 * intensity.clamp(b));

    out << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
}