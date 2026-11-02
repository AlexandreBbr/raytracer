#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "Camera.hpp"
#include "lights/ILight.hpp"
#include "primitives/IPrimitive.hpp"

#include <memory>
#include <vector>

namespace raytracer {
    struct Scene {
        Camera camera;
        std::vector<std::unique_ptr<primitives::IPrimitive>> primitives;
        std::vector<std::unique_ptr<lights::ILight>> lights;
        math::Vector3 ambient{0.1, 0.1, 0.1};
        math::Vector3 background{0.05, 0.05, 0.08};
        int maxDepth = 5;
        int antialiasing = 2;

        bool intersect(const math::Ray &ray, double tMin, double tMax, primitives::Hit &hit) const;
    };
}

#endif
