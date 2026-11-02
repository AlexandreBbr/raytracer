#include "Camera.hpp"

#include <cmath>

namespace raytracer {
    Camera::Camera(const math::Vector3 &position, const math::Vector3 &rotation, double fov, int width, int height)
        : _position(position), _orientation({}, rotation),
          _scale(std::tan(fov * M_PI / 360.0)), _width(width), _height(height)
    {
    }

    math::Ray Camera::ray(double px, double py) const
    {
        double aspect = static_cast<double>(_width) / _height;
        double x = (2 * px / _width - 1) * _scale;
        double y = (1 - 2 * py / _height) * _scale / aspect;

        return {_position, _orientation.toWorld(math::Vector3(x, y, -1).normalized())};
    }
}
