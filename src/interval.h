#pragma once

class interval {
public:
    float min, max;

    interval() : min(+infinity), max(-infinity) {}
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
    static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::empty = interval(-infinity, +infinity);
