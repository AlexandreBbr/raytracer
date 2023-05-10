/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_
#include <iostream>
#include <libconfig.h++>

namespace raytracer {
    class Parser {
        public:
            Parser();
            ~Parser();
            void parseFile(const std::string &filename);
            void parseCamera(const libconfig::Setting &camera);
            void parseLights(const libconfig::Setting &light);
            void parsePrimitives(const libconfig::Setting &primitives);
        protected:
        private:
    };
};

#endif /* !PARSER_HPP_ */
