/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** Plane
*/

#include "IObject.hpp"

#ifndef PLANE_HPP_
#define PLANE_HPP_

namespace raytracer {
    namespace objects {

        class Plane : public raytracer::objects::AObject {
            public:
                Plane(sf::Vector3f pos, sf::Vector3f rot, sf::Vector3f scale);
                ~Plane();
            protected:
            private:
        };
    };
};

#endif /* !PLANE_HPP_ */
