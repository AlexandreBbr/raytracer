/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** Display
*/

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include "Raytracer.hpp"

namespace raytracer {
    class Pixel {
        public:
            Pixel();
            ~Pixel();

            sf::Uint8 *pixel;
        protected:
        private:
    };
    class Display {
        public:
            Display();
            ~Display();
            void launchScene();
            void poolEvent();

        protected:
        raytracer::Pixel *_pixels;
        sf::RenderWindow *_window;
        sf::Sprite *_sprite;
        sf::Texture _texture;
        sf::Event _event;
        private:
    };
};

#endif /* !DISPLAY_HPP_ */
