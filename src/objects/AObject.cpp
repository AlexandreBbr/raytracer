/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** AObject
*/

#include "../../include/objects/IObject.hpp"

void Raytracer::AObject::setPos(sf::Vector3f pos)
{
    this->_position = pos;
}

sf::Vector3f Raytracer::AObject::getPos()
{
    return this->_position;
}

void Raytracer::AObject::setRot(sf::Vector3f rot)
{
    this->_rotation = rot;
}

sf::Vector3f Raytracer::AObject::getRot()
{
    return this->_rotation;
}

void Raytracer::AObject::setScale(sf::Vector3f scale)
{
    this->_scale = scale;
}

sf::Vector3f Raytracer::AObject::getScale()
{
    return this->_scale;
}