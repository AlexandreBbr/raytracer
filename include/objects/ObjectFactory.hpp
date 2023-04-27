/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** ObjectFactory
*/

#include <string>
#include <iostream>
#include "IObject.hpp"

#ifndef OBJECTFACTORY_HPP_
#define OBJECTFACTORY_HPP_

namespace raytracer {
    class ObjectFactory {
        public:
            ObjectFactory();
            ~ObjectFactory();

            void create(raytracer::objects::ObjectType type, sf::Vector3f pos);
            void create(raytracer::objects::ObjectType type, sf::Vector3f pos, sf::Vector3f rot, sf::Vector3f scale);
        protected:
    };
};


#endif /* !OBJECTFACTORY_HPP_ */
