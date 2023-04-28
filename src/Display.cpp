/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** Display
*/

#include "../include/Display.hpp"

raytracer::Display::Display()
{
    _window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Raytracer");
    _texture.create(1, 1);
    _sprite = new sf::Sprite(_texture);
    _pixels = new(raytracer::Pixel);
}

raytracer::Display::~Display()
{
    _window->close();
    delete _window;
}

void raytracer::Display::poolEvent()
{
    while (_window->isOpen())
    {
        while (_window->pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed)
                return;
        }
    }
}

void raytracer::Display::launchScene()
{    
    _texture.update(_pixels->pixel);
    for (int x = 0; x < 50; x++)
    {
        for (int y = 0; y < 50; y++)
        {
            _sprite->setPosition(x, y);
            _window->draw(*(_sprite));
        }
    }
    _window->display();
    this->poolEvent();
    return;
}
