#pragma once

#include "vec3.h"


using colour = vec3;

void write_colour(std::ostream& out, const colour& pixel_colour) {
    auto r = pixel_colour.x();
    auto g = pixel_colour.y();
    auto b = pixel_colour.z();

    //transalte [0,1] component values to the byte range [0,255]
    int r_byte = int(255.999 * r);
    int g_byte = int(255.999 * g);
    int b_byte = int(255.999 * b);

    out << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
}