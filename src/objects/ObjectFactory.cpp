/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** ObjectFactory
*/

#include "../../include/objects/ObjectFactory.hpp"
#include "../../include/objects/Sphere.hpp"
#include "../../include/objects/Plane.hpp"

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
            this->objects.push_back(new raytracer::objects::Sphere(pos, rot, scale));
            break;
        case raytracer::objects::PLANE:
            this->objects.push_back(new raytracer::objects::Plane(pos, rot, scale));
            break;
    }
}