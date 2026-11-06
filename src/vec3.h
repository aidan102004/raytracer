#pragma once

#include <cmath>
#include <iostream>

class vec3 {
public:
    float e[3];

    vec3() : e{0,0,0} {}
    vec3(float e0, float e1, float e2) : e{e0, e1, e2} {}

    float x() const {return e[0];}
    float y() const {return e[1];}
    float z() const {return e[2];}

    vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
    float operator[](int i) const {return e[i];}
    float& operator[](int i) {return e[i];}

    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(float t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(float t) {
        return *this *= 1/t;
    }
    float length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    float len() const {
        return std::sqrt(length_squared());
    }
};


using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& v1, const vec3& v2) {
    float e0 = v1.e[0] + v2.e[0];
    float e1 = v1.e[1] + v2.e[1];
    float e2 = v1.e[2] + v2.e[2];
    return vec3(e0,e1,e2);
}

inline vec3 operator-(const vec3& v1, const vec3& v2) {
    float e0 = v1.e[0] - v2.e[0];
    float e1 = v1.e[1] - v2.e[1];
    float e2 = v1.e[2] - v2.e[2];
    return vec3(e0,e1,e2);
}

inline vec3 operator*(const vec3& v1, const vec3& v2) {
    float e0 = v1.e[0] * v2.e[0];
    float e1 = v1.e[1] * v2.e[1];
    float e2 = v1.e[2] * v2.e[2];
    return vec3(e0,e1,e2);
}

inline vec3 operator*(double t, const vec3& v) {
    float e0 = v.e[0] * t;
    float e1 = v.e[1] * t;
    float e2 = v.e[2] * t;
    return vec3(e0,e1,e2);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

inline float dot(const vec3& v1, const vec3& v2) {
    return (v1.e[0] * v2.e[0]) + (v1.e[1] * v2.e[1]) + (v1.e[2] * v2.e[2]);
}

inline vec3 cross(const vec3& v1, const vec3& v2) {
    return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
                v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}
//returns new normalised unit vector
inline vec3 normalise(const vec3& v) {
    return v / v.len();
}

