#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "math/Vector3.hpp"

namespace raytracer::math {
    // Rotation in degrees, applied in X then Y then Z order.
    class Transform {
        public:
            Transform() = default;
            Transform(const Vector3 &translation, const Vector3 &rotation);

            Vector3 toWorld(const Vector3 &v) const;
            Vector3 toLocal(const Vector3 &v) const;
            Vector3 pointToLocal(const Vector3 &p) const { return toLocal(p - _translation); }
            Ray rayToLocal(const Ray &ray) const;

        private:
            Vector3 _translation;
            double _m[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    };
}

#endif
