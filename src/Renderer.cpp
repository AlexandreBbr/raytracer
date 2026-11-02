#include "Renderer.hpp"

#include <algorithm>
#include <atomic>
#include <cmath>
#include <limits>
#include <thread>

namespace raytracer {
    using math::Ray;
    using math::Vector3;

    static constexpr double EPSILON = 1e-6;

    Vector3 Renderer::shade(const Ray &ray, const primitives::Hit &hit) const
    {
        const primitives::Material &mat = hit.object->getMaterial();
        Vector3 color = _scene.ambient * mat.color;
        Vector3 origin = hit.point + hit.normal * EPSILON;

        for (const auto &light : _scene.lights) {
            lights::LightSample s = light->sample(hit.point);
            double diffuse = hit.normal.dot(s.direction);
            primitives::Hit blocker;

            if (diffuse <= 0 || _scene.intersect({origin, s.direction}, EPSILON, s.distance, blocker))
                continue;
            Vector3 reflected = (-s.direction).reflect(hit.normal);
            double specular = std::pow(std::max(0.0, reflected.dot(-ray.direction)), mat.shininess);
            color += s.radiance * (mat.color * diffuse + Vector3(1, 1, 1) * (mat.specular * specular));
        }
        return color;
    }

    Vector3 Renderer::trace(const Ray &ray, int depth) const
    {
        primitives::Hit hit;

        if (!_scene.intersect(ray, EPSILON, std::numeric_limits<double>::infinity(), hit))
            return _scene.background;
        Vector3 color = shade(ray, hit);
        double reflection = hit.object->getMaterial().reflection;
        if (reflection > 0 && depth < _scene.maxDepth) {
            Ray bounce{hit.point + hit.normal * EPSILON, ray.direction.reflect(hit.normal)};
            color = color * (1 - reflection) + trace(bounce, depth + 1) * reflection;
        }
        return color;
    }

    Vector3 Renderer::renderPixel(int x, int y) const
    {
        int n = std::max(1, _scene.antialiasing);
        Vector3 sum;

        for (int sy = 0; sy < n; sy++)
            for (int sx = 0; sx < n; sx++)
                sum += trace(_scene.camera.ray(x + (sx + 0.5) / n, y + (sy + 0.5) / n), 0);
        return sum / (n * n);
    }

    Image Renderer::render(unsigned threads) const
    {
        Image image{_scene.camera.getWidth(), _scene.camera.getHeight(), {}};
        std::atomic<int> nextRow{0};
        std::vector<std::thread> workers;

        image.pixels.resize(static_cast<size_t>(image.width) * image.height);
        auto work = [&] {
            for (int y = nextRow++; y < image.height; y = nextRow++)
                for (int x = 0; x < image.width; x++)
                    image.pixels[static_cast<size_t>(y) * image.width + x] = renderPixel(x, y);
        };
        for (unsigned i = 0; i < std::max(1u, threads); i++)
            workers.emplace_back(work);
        for (auto &w : workers)
            w.join();
        return image;
    }
}
