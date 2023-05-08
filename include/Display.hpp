/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** Display
*/

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include "Raytracer.hpp"
#include "objects/Sphere.hpp"


namespace raytracer {
    class Maths {
        public:
            Maths();
            ~Maths();
            bool inter;
            sf::Vector3f pos;
            void intersect(sf::Vector3f cam, sf::Vector3f rot, raytracer::objects::Sphere sphere)
            {
                float a;
                float b;
                float c;
                float delta;
                float t1, t2;
                float vx = rand() % 1000 / 1000.0f;
                float vy = rand() % 1000 / 1000.0f;
                float vz = rand() % 1000 / 1000.0f;
                if (rand() % 1 == 1)
                    vx *= -1;
                if (rand() % 1 == 1)
                    vy *= -1;
                if (rand() % 1 == 1)
                    vz *= -1;
                a = pow(vx, 2) + pow(vy, 2) + pow(vz, 2);
                b = 2 * (vx * (cam.x - sphere.center.x) + vy * (cam.y - sphere.center.y) + vz * (cam.z - sphere.center.z));
                c = pow(cam.x - sphere.center.x, 2) + pow(cam.y - sphere.center.y, 2) + pow(cam.z - sphere.center.z, 2) - pow(sphere.radius, 2);
                delta = pow(b, 2) - 4 * a * c;
                if (delta >= 0) {
                    this->inter = true;
                    t1 = -b + sqrt(delta) / (2 * a);
                    t2 = -b - sqrt(delta) / (2 * a);
                    if (t1 <= t2) {
                        pos.x = vx * t1 + cam.x;
                        pos.y = vy * t1 + cam.y;
                        pos.z = vz * t1 + cam.z;   
                    }
                    else {
                        pos.x = vx * t2 + cam.x;
                        pos.y = vy * t2 + cam.y;
                        pos.z = vz * t2 + cam.z;   
                    }
                }
            }
    };
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
            sf::Vector3f normalize(int x, int z);
            void poolEvent();

        protected:
        raytracer::Pixel *_pixels;
        sf::RenderWindow *_window;
        sf::Sprite *_sprite;
        sf::Texture *_texture;
        sf::Event _event;
        sf::Image image;
        sf::Vector3f _rayDirection;
        bool _isInit;
        int _width;
        int _height;
        private:
    };
};

#endif /* !DISPLAY_HPP_ */
