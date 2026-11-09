#pragma once

#include "interval.h"
#include "vec3.h"


using colour = vec3;

void write_colour(std::ostream& out, const colour& pixel_colour) {
    auto r = pixel_colour.x();
    auto g = pixel_colour.y();
    auto b = pixel_colour.z();

    //transalte [0,1] component values to the byte range [0,255]
    static const interval intensity(0.000, 0.999); //saftey net for clamping
    int r_byte = int(256 * intensity.clamp(r));
    int g_byte = int(256 * intensity.clamp(g));
    int b_byte = int(256 * intensity.clamp(b));

    out << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
}