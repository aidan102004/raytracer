#pragma once

class interval {
public:
    float min, max;

    interval() : min(+infinity), max(-infinity) {} //default to empty for saftey
    interval(float min, float max) : min(min), max(max) {}
    float size() const {
        return max-min;
    }
    //inclusive
    bool contains(float x) {
        return min <= x && x <= max;
    }
    //exclusive
    bool surrounds(float x) {
        return min < x && x < max;
    }

    float clamp(float x) const {
        if (x<min) return min;
        if (x>max) return max;
        return x;
    }
    static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity); //no numbers will satisfy as min is larger than max
const interval interval::universe = interval(-infinity, +infinity); //all numbers should satisfy
