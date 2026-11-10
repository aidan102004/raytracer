#pragma once


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

    //checks if all elements of vector are close to zero
    bool near_zero() const {
        auto s = 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
    }

    static vec3 random_vec() {
        return vec3(random_float(), random_float(), random_float());
    }

    static vec3 random_vec(float min, float max) {
        return vec3(random_float(min,max), random_float(min,max), random_float(min,max));
    }
};


using point3 = vec3;

/*for printing vectors for debugging*/
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

inline vec3 random_unit_vec() {
    //loop until we find an appropriate vector
    while (true) {
        auto v = vec3::random_vec(-1,1); //generate vector in the a cube [-1, 1]
        float sqr = v.length_squared();
        //ensure it is within the sphere
        if (1e-160 < sqr && sqr <= 1) {
            return normalise(v); //normalise
        }
    }
}
/*generates a random unit vector on the hemipshere*/
inline vec3 generate_random(const vec3& normal) {
    vec3 v = random_unit_vec(); //generates random unit vector
    if (dot(v, normal) < 0.0) //finds out whether this vector points away from  the surface, the dp will be < 0 if it doesnt, so we flip it
        return -v;
    else 
        return v;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}

