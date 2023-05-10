/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** ACamera
*/

#include "../../include/objects/Camera.hpp"

raytracer::objects::Camera::Camera()
{
}

raytracer::objects::Camera::~Camera()
{
}

void raytracer::objects::Camera::setFov(float fov)
{
    this->fov = fov;
}

float raytracer::objects::Camera::getFov()
{
    return this->fov;
}

void raytracer::objects::Camera::setResolution(int width, int height)
{
    this->resolution[0] = width;
    this->resolution[1] = height;
}

std::pair<int, int> raytracer::objects::Camera::getResolution()
{
    return std::make_pair(this->resolution[0], this->resolution[1]);
}
