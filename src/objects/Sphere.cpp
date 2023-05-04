/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** Sphere
*/

#include "../../include/objects/Sphere.hpp"

raytracer::objects::Sphere::Sphere(sf::Vector3f pos, sf::Vector3f rot, sf::Vector3f scale)
{
    this->setPos(pos);
    this->setRot(rot);
    this->setScale(scale);
}

raytracer::objects::Sphere::~Sphere()
{
}
