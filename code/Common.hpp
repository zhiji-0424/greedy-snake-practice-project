#ifndef SNAKE_COMMON_HPP
#define SNAKE_COMMON_HPP

#include <cmath>

// #define my_is_equal(a, b) (fabs(a - b) < 1e-9)

// struct vec2 {
//     float x, y;
//     vec2() : x(0), y(0) {}
//     vec2(float x, float y) : x(x), y(y) {}
//     vec2 operator+(const vec2& other) const { return vec2(x + other.x, y + other.y); }
//     vec2 operator-(const vec2& other) const { return vec2(x - other.x, y - other.y); }
//     vec2 operator+=(const vec2& other) { return *this = *this + other; }
//     // bool operator==(const vec2& other) const { return my_is_equal(x, other.x) && my_is_equal(y, other.y); }
//     vec2 operator*(float k) const { return vec2(x * k, y * k); }
//     float size() const { return sqrt(x * x + y * y); }
// };

// struct vec3 {
//     float x, y, z;
//     vec3() : x(0), y(0), z(0) {}
//     vec3(float x, float y, float z) : x(x), y(y), z(z) {}
//     vec3 operator+(const vec3& other) const { return vec3(x + other.x, y + other.y, z + other.z); }
//     vec3 operator-(const vec3& other) const { return vec3(x - other.x, y - other.y, z - other.z); }
//     vec3 operator+=(const vec3& other) { return *this = *this + other; }
//     // bool operator==(const vec3& other) const { return my_is_equal(x, other.x) && my_is_equal(y, other.y) && my_is_equal(z, other.z); }
//     vec3 operator*(float k) const { return vec3(x * k, y * k, z * k); }
//     float size() const { return sqrt(x * x + y * y + z * z); }
// };

struct vec4 {
    float x, y, z, w;
    vec4() : x(0), y(0), z(0), w(0) {}
    vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    vec4 operator+(const vec4& other) const { return vec4(x + other.x, y + other.y, z + other.z, w + other.w); }
    vec4 operator-(const vec4& other) const { return vec4(x - other.x, y - other.y, z - other.z, w - other.w); }
    vec4 operator+=(const vec4& other) { return *this = *this + other; }
    // bool operator==(const vec4& other) const { return my_is_equal(x, other.x) && my_is_equal(y, other.y) && my_is_equal(z, other.z) && my_is_equal(w, other.w); }
    vec4 operator*(float k) const { return vec4(x * k, y * k, z * k, w * k); }
    float size() const { return sqrt(x * x + y * y + z * z + w * w); }
};

// #undef my_is_equal

#endif
