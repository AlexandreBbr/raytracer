#include "math/Transform.hpp"

namespace raytracer::math {
    static constexpr double DEG = M_PI / 180.0;

    Transform::Transform(const Vector3 &translation, const Vector3 &rotation)
        : _translation(translation)
    {
        double cx = std::cos(rotation.x * DEG), sx = std::sin(rotation.x * DEG);
        double cy = std::cos(rotation.y * DEG), sy = std::sin(rotation.y * DEG);
        double cz = std::cos(rotation.z * DEG), sz = std::sin(rotation.z * DEG);

        _m[0][0] = cy * cz;
        _m[0][1] = sx * sy * cz - cx * sz;
        _m[0][2] = cx * sy * cz + sx * sz;
        _m[1][0] = cy * sz;
        _m[1][1] = sx * sy * sz + cx * cz;
        _m[1][2] = cx * sy * sz - sx * cz;
        _m[2][0] = -sy;
        _m[2][1] = sx * cy;
        _m[2][2] = cx * cy;
    }

    Vector3 Transform::toWorld(const Vector3 &v) const
    {
        return {
            _m[0][0] * v.x + _m[0][1] * v.y + _m[0][2] * v.z,
            _m[1][0] * v.x + _m[1][1] * v.y + _m[1][2] * v.z,
            _m[2][0] * v.x + _m[2][1] * v.y + _m[2][2] * v.z,
        };
    }

    Vector3 Transform::toLocal(const Vector3 &v) const
    {
        return {
            _m[0][0] * v.x + _m[1][0] * v.y + _m[2][0] * v.z,
            _m[0][1] * v.x + _m[1][1] * v.y + _m[2][1] * v.z,
            _m[0][2] * v.x + _m[1][2] * v.y + _m[2][2] * v.z,
        };
    }

    Ray Transform::rayToLocal(const Ray &ray) const
    {
        return {pointToLocal(ray.origin), toLocal(ray.direction)};
    }
}
