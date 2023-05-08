/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** main
*/

#include "../include/Display.hpp"

int main(int ac, char **av)
{
    raytracer::Raytracer core;
    raytracer::Display *ray = new raytracer::Display();
    ray->launchScene();
    delete ray;
    return (0);
}