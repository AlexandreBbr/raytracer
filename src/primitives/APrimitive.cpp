#include "primitives/IPrimitive.hpp"

#include <cmath>
#include <utility>

namespace raytracer::primitives {
    bool APrimitive::intersect(const Ray &ray, double tMin, double tMax, Hit &hit) const
    {
        Vector3 localNormal;
        double t = 0;

        if (!intersectLocal(_transform.rayToLocal(ray), tMin, tMax, t, localNormal))
            return false;
        hit.t = t;
        hit.point = ray.at(t);
        hit.normal = _transform.toWorld(localNormal).normalized();
        if (hit.normal.dot(ray.direction) > 0)
            hit.normal = -hit.normal;
        hit.object = this;
        return true;
    }

    bool solveQuadratic(double a, double b, double c, double &t0, double &t1)
    {
        if (std::abs(a) < 1e-12)
            return false;
        double delta = b * b - 4 * a * c;
        if (delta < 0)
            return false;
        double sq = std::sqrt(delta);
        t0 = (-b - sq) / (2 * a);
        t1 = (-b + sq) / (2 * a);
        if (t0 > t1)
            std::swap(t0, t1);
        return true;
    }
}
