#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <cmath>

namespace raytracer::math {
    struct Vector3 {
        double x = 0;
        double y = 0;
        double z = 0;

        constexpr Vector3() = default;
        constexpr Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

        constexpr Vector3 operator+(const Vector3 &o) const { return {x + o.x, y + o.y, z + o.z}; }
        constexpr Vector3 operator-(const Vector3 &o) const { return {x - o.x, y - o.y, z - o.z}; }
        constexpr Vector3 operator*(const Vector3 &o) const { return {x * o.x, y * o.y, z * o.z}; }
        constexpr Vector3 operator*(double k) const { return {x * k, y * k, z * k}; }
        constexpr Vector3 operator/(double k) const { return {x / k, y / k, z / k}; }
        constexpr Vector3 operator-() const { return {-x, -y, -z}; }
        Vector3 &operator+=(const Vector3 &o) { x += o.x; y += o.y; z += o.z; return *this; }

        constexpr double dot(const Vector3 &o) const { return x * o.x + y * o.y + z * o.z; }
        constexpr Vector3 cross(const Vector3 &o) const
        {
            return {y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x};
        }
        double length() const { return std::sqrt(dot(*this)); }
        Vector3 normalized() const { return *this / length(); }
        Vector3 reflect(const Vector3 &normal) const { return *this - normal * (2 * dot(normal)); }
    };

    inline Vector3 operator*(double k, const Vector3 &v) { return v * k; }

    struct Ray {
        Vector3 origin;
        Vector3 direction;

        Vector3 at(double t) const { return origin + direction * t; }
    };
}

#endif
