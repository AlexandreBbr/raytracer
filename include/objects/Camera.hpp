/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** Camera
*/

#include "IObject.hpp"

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

namespace raytracer {
    namespace objects {
        
        class Camera : public raytracer::objects::AObject {
            public:
                Camera();
                ~Camera();
                void setFov(float fov);
                float getFov();
                void setResolution(int width, int height);
                std::pair<int, int> getResolution();
            protected:
                float fov;
                int resolution[];
            private:
        };
    };
};

#endif /* !CAMERA_HPP_ */
