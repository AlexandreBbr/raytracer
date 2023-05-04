/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** Plane
*/

#include "../../include/objects/Plane.hpp"

raytracer::objects::Plane::Plane(sf::Vector3f pos, sf::Vector3f rot, sf::Vector3f scale)
{
    this->setPos(pos);
    this->setRot(rot);
    this->setScale(scale);
}

raytracer::objects::Plane::~Plane()
{
}
