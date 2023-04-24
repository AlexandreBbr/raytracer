/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** AObject
*/

#include "../../include/objects/IObject.hpp"

void AObject::setPos(sf::Vector3f pos)
{
    this->position = pos;
}

sf::Vector3f AObject::getPos()
{
    return this->position;
}

void AObject::setRot(sf::Vector3f rot)
{
    this->rotation = rot;
}

sf::Vector3f AObject::getRot()
{
    return this->rotation;
}

void AObject::setScale(sf::Vector3f scale)
{
    this->scale = scale;
}

sf::Vector3f AObject::getScale()
{
    return this->scale;
}