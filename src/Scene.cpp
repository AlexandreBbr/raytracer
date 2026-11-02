#include "Scene.hpp"

namespace raytracer {
    bool Scene::intersect(const math::Ray &ray, double tMin, double tMax, primitives::Hit &hit) const
    {
        bool found = false;

        for (const auto &primitive : primitives) {
            if (primitive->intersect(ray, tMin, tMax, hit)) {
                tMax = hit.t;
                found = true;
            }
        }
        return found;
    }
}
