/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** ObjectFactory
*/

#include "../../include/objects/ObjectFactory.hpp"

raytracer::ObjectFactory::ObjectFactory()
{
}

raytracer::ObjectFactory::~ObjectFactory()
{
}

void raytracer::ObjectFactory::create(raytracer::objects::ObjectType type, sf::Vector3f pos)
{
    this->create(type, pos, sf::Vector3f(0, 0, 0), sf::Vector3f(1, 1, 1));
}

void raytracer::ObjectFactory::create(raytracer::objects::ObjectType type, sf::Vector3f pos, sf::Vector3f rot, sf::Vector3f scale)
{
    switch (type) {
        case raytracer::objects::SPHERE:
            std::cout << "Creating SPHERE" << std::endl;
            break;
        case raytracer::objects::PLANE:
            std::cout << "Creating PLANE" << std::endl;
            break;
    }
}