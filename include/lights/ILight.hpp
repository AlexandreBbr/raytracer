#ifndef ILIGHT_HPP_
#define ILIGHT_HPP_

#include "math/Vector3.hpp"

#include <limits>

namespace raytracer::lights {
    using math::Vector3;

    struct LightSample {
        Vector3 direction;
        double distance = std::numeric_limits<double>::infinity();
        Vector3 radiance;
    };

    class ILight {
        public:
            virtual ~ILight() = default;
            virtual LightSample sample(const Vector3 &point) const = 0;
    };

    class DirectionalLight : public ILight {
        public:
            DirectionalLight(const Vector3 &direction, const Vector3 &radiance)
                : _toLight(-direction.normalized()), _radiance(radiance) {}

            LightSample sample(const Vector3 &) const override
            {
                return {_toLight, std::numeric_limits<double>::infinity(), _radiance};
            }

        private:
            Vector3 _toLight;
            Vector3 _radiance;
    };

    class PointLight : public ILight {
        public:
            PointLight(const Vector3 &position, const Vector3 &radiance)
                : _position(position), _radiance(radiance) {}

            LightSample sample(const Vector3 &point) const override
            {
                Vector3 d = _position - point;
                double dist = d.length();
                return {d / dist, dist, _radiance};
            }

        private:
            Vector3 _position;
            Vector3 _radiance;
    };
}

#endif
