#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "math/Transform.hpp"

namespace raytracer {
    // Looks down -z before rotation. fov is horizontal, in degrees.
    class Camera {
        public:
            Camera() = default;
            Camera(const math::Vector3 &position, const math::Vector3 &rotation, double fov, int width, int height);

            math::Ray ray(double px, double py) const;
            int getWidth() const { return _width; }
            int getHeight() const { return _height; }

        private:
            math::Vector3 _position;
            math::Transform _orientation;
            double _scale = 1;
            int _width = 800;
            int _height = 600;
    };
}

#endif
