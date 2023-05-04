/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** Raytracer
*/

#include "Parser.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#ifndef RAYTRACER_HPP_
#define RAYTRACER_HPP_

namespace raytracer {
    class Raytracer {
        public:
            Raytracer();
            ~Raytracer();
            raytracer::Parser parser;
        protected:
        private:
    };
};

#endif /* !RAYTRACER_HPP_ */
