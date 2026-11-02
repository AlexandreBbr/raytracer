#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "Scene.hpp"

#include <string>
#include <vector>

namespace raytracer {
    struct Image {
        int width = 0;
        int height = 0;
        std::vector<math::Vector3> pixels;

        void save(const std::string &path) const;
    };

    class Renderer {
        public:
            explicit Renderer(const Scene &scene) : _scene(scene) {}

            Image render(unsigned threads) const;

        private:
            math::Vector3 trace(const math::Ray &ray, int depth) const;
            math::Vector3 shade(const math::Ray &ray, const primitives::Hit &hit) const;
            math::Vector3 renderPixel(int x, int y) const;

            const Scene &_scene;
    };
}

#endif
