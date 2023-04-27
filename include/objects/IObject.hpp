/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** IObject
*/

#include "SFML/System.hpp"

#ifndef IOBJECT_HPP_
#define IOBJECT_HPP_

namespace raytracer {
    namespace objects {
        enum ObjectType {
            SPHERE,
            PLANE
        };

        class IObject {
            public:
                IObject() = default;
                ~IObject() = default;
                virtual void setPos(sf::Vector3f pos) = 0;
                virtual sf::Vector3f getPos() = 0;
                virtual void setRot(sf::Vector3f rot) = 0;
                virtual sf::Vector3f getRot() = 0;
                virtual void setScale(sf::Vector3f scale) = 0;
                virtual sf::Vector3f getScale() = 0;
            protected:
                sf::Vector3f position;
                sf::Vector3f rotation;
                sf::Vector3f scale;
        };

        class AObject : public IObject {
            public:
                AObject() = default;
                ~AObject() = default;
                void setPos(sf::Vector3f pos) override;
                sf::Vector3f getPos() override;
                void setRot(sf::Vector3f rot) override;
                sf::Vector3f getRot() override;
                void setScale(sf::Vector3f scale) override;
                sf::Vector3f getScale() override;
            protected:
                sf::Vector3f _position;
                sf::Vector3f _rotation;
                sf::Vector3f _scale;
        };
    };
};

#endif /* !IOBJECT_HPP_ */
