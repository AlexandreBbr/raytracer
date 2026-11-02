#ifndef PRIMITIVES_HPP_
#define PRIMITIVES_HPP_

#include "primitives/IPrimitive.hpp"

namespace raytracer::primitives {
    class Sphere : public APrimitive {
        public:
            Sphere(const math::Transform &transform, const Material &material, double radius)
                : APrimitive(transform, material), _radius(radius) {}

        protected:
            bool intersectLocal(const Ray &ray, double tMin, double tMax,
                double &t, Vector3 &normal) const override;

        private:
            double _radius;
    };

    // Infinite plane y = 0, rotate it to get other orientations.
    class Plane : public APrimitive {
        public:
            using APrimitive::APrimitive;

        protected:
            bool intersectLocal(const Ray &ray, double tMin, double tMax,
                double &t, Vector3 &normal) const override;
    };

    // Closed cylinder along y, from y = 0 to y = height.
    class Cylinder : public APrimitive {
        public:
            Cylinder(const math::Transform &transform, const Material &material, double radius, double height)
                : APrimitive(transform, material), _radius(radius), _height(height) {}

        protected:
            bool intersectLocal(const Ray &ray, double tMin, double tMax,
                double &t, Vector3 &normal) const override;

        private:
            double _radius;
            double _height;
    };

    // Base of the given radius at y = 0, apex at y = height.
    class Cone : public APrimitive {
        public:
            Cone(const math::Transform &transform, const Material &material, double radius, double height)
                : APrimitive(transform, material), _radius(radius), _height(height) {}

        protected:
            bool intersectLocal(const Ray &ray, double tMin, double tMax,
                double &t, Vector3 &normal) const override;

        private:
            double _radius;
            double _height;
    };
}

#endif
