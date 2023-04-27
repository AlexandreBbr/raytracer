/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** AObject
*/

#include "../../include/objects/IObject.hpp"

void raytracer::objects::AObject::setPos(sf::Vector3f pos)
{
    this->_position = pos;
}

sf::Vector3f raytracer::objects::AObject::getPos()
{
    return this->_position;
}

void raytracer::objects::AObject::setRot(sf::Vector3f rot)
{
    this->_rotation = rot;
}

sf::Vector3f raytracer::objects::AObject::getRot()
{
    return this->_rotation;
}

void raytracer::objects::AObject::setScale(sf::Vector3f scale)
{
    this->_scale = scale;
}

sf::Vector3f raytracer::objects::AObject::getScale()
{
    return this->_scale;
}