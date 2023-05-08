/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** Sphere
*/

#include "IObject.hpp"
#include <cmath>
#include <SFML/Graphics/Color.hpp>

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

namespace raytracer {
    namespace objects {
        class Sphere : public raytracer::objects::AObject {
            public:
                Sphere(sf::Vector3f pos, sf::Vector3f rot, sf::Vector3f scale);
                ~Sphere();
                sf::Vector3f center;
                float radius;
                //sf::Uint8 *color = new sf::Uint8[4] {0, 0, 0, 255};
                sf::Color color;
                sf::Vector3f scale;
                sf::Vector3f rot;
                sf::Vector3f pos;
                bool intersect(const sf::Vector3f& rayOrigin, const sf::Vector3f& rayDirection, float& t) const
                {
                    sf::Vector3f L = center - rayOrigin;
                    float tca = L.x*rayDirection.x + L.y*rayDirection.y + L.z*rayDirection.z;
                    float d2 = L.x*L.x + L.y*L.y + L.z*L.z - tca*tca;
                    if (d2 > radius*radius) 
                        return false;
                    float thc = sqrt(radius*radius - d2);
                    float t0 = tca - thc;
                    float t1 = tca + thc;
                    if (t0 > t1) std::swap(t0, t1);
                    if (t0 < 0) {
                        t0 = t1; 
                        if (t0 < 0) return false;
                    }
                    t = t0;
                    return true;
                }
                sf::Vector3f trace(const sf::Vector3f& rayOrigin, const sf::Vector3f& rayDirection, const std::vector<Sphere>& spheres)
        {
            float tMin = INFINITY;
            const Sphere* hitSphere = nullptr;
            for (size_t i = 0; i < spheres.size(); i++) {
                float t = 0;
                if (spheres[i].intersect(rayOrigin, rayDirection, t) && t < tMin) {
                    tMin = t;
                    hitSphere = &spheres[i];
                }
            }
            if (!hitSphere) return sf::Vector3f(0.2f, 0.7f, 0.8f); // background color
            sf::Vector3f hitPoint = rayOrigin + rayDirection*tMin;
            sf::Vector3f N;
            N.x = (hitPoint - hitSphere->center).x*rayDirection.x;
            N.y = (hitPoint - hitSphere->center).y*rayDirection.y;
            N.z = (hitPoint - hitSphere->center).z*rayDirection.z;
            N = N / std::sqrt(N.x*N.x + N.y*N.y + N.z*N.z);
            float diffuse = 0.6f;
            float ambient = 0.4f;
            sf::Vector3f color = hitSphere->center.x*hitSphere->center.y*hitSphere->center.z*sf::Vector3f(diffuse, diffuse, diffuse) + sf::Vector3f(ambient, ambient, ambient);
            return color;
        }
        };
    };
};
#endif /* !SPHERE_HPP_ */
