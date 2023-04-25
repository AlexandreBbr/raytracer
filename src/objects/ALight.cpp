/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** ALight
*/

#include "../../include/objects/ILight.hpp"

void Raytracer::ALight::setIntensity(float intensity)
{
    this->_intensity = intensity;
}

float Raytracer::ALight::getIntensity()
{
    return this->_intensity;
}