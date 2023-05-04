/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** Sphere
*/

#include "IObject.hpp"

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

namespace raytracer {
    namespace objects {
        class Sphere : public raytracer::objects::AObject {
            public:
                Sphere(sf::Vector3f pos, sf::Vector3f rot, sf::Vector3f scale);
                ~Sphere();
            protected:
            private:
        };
    };
};

#endif /* !SPHERE_HPP_ */
