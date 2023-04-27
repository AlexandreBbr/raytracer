/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** ILight
*/

#include "IObject.hpp"

#ifndef ILIGHT_HPP_
#define ILIGHT_HPP_

namespace raytracer {
    class ILight : public raytracer::objects::AObject {
        public:
            virtual ~ILight() = default;
            virtual void setIntensity(float intensity) = 0;
            virtual float getIntensity() = 0;
        protected:
            float intensity;
    };

    class ALight : public ILight {
        public:
            ALight() = default;
            ~ALight() = default;
            void setIntensity(float intensity) override;
            float getIntensity() override;
        protected:
            float _intensity;
    };
};


#endif /* !ILIGHT_HPP_ */
