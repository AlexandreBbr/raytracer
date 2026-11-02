#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "ObjectFactory.hpp"
#include "Scene.hpp"

#include <libconfig.h++>
#include <string>

namespace raytracer {
    class Parser {
        public:
            Scene parseFile(const std::string &filename) const;

        private:
            void parseCamera(const libconfig::Setting &camera, Scene &scene) const;
            void parseRender(const libconfig::Setting &render, Scene &scene) const;
            void parsePrimitives(const libconfig::Setting &primitives, Scene &scene) const;
            void parseLights(const libconfig::Setting &lights, Scene &scene) const;

            ObjectFactory _factory;
    };
}

#endif
