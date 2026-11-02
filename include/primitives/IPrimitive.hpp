#ifndef IPRIMITIVE_HPP_
#define IPRIMITIVE_HPP_

#include "math/Transform.hpp"

namespace raytracer::primitives {
    using math::Ray;
    using math::Vector3;

    struct Material {
        Vector3 color{1, 1, 1};
        double reflection = 0;
        double specular = 0.3;
        double shininess = 32;
    };

    class IPrimitive;

    struct Hit {
        double t = 0;
        Vector3 point;
        Vector3 normal;
        const IPrimitive *object = nullptr;
    };

    class IPrimitive {
        public:
            virtual ~IPrimitive() = default;
            virtual bool intersect(const Ray &ray, double tMin, double tMax, Hit &hit) const = 0;
            virtual const Material &getMaterial() const = 0;
    };

    // Each primitive is defined around the origin in its own space, rays are moved there.
    class APrimitive : public IPrimitive {
        public:
            APrimitive(const math::Transform &transform, const Material &material)
                : _transform(transform), _material(material) {}

            bool intersect(const Ray &ray, double tMin, double tMax, Hit &hit) const override;
            const Material &getMaterial() const override { return _material; }

        protected:
            virtual bool intersectLocal(const Ray &ray, double tMin, double tMax,
                double &t, Vector3 &normal) const = 0;

        private:
            math::Transform _transform;
            Material _material;
    };

    bool solveQuadratic(double a, double b, double c, double &t0, double &t1);
}

#endif
