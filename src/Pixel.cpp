/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** Pixel
*/

#include "../include/Display.hpp"

raytracer::Pixel::Pixel()
{
    pixel = new sf::Uint8[4] {255, 0, 0, 255}; // RGBA
}

raytracer::Pixel::~Pixel()
{
}
