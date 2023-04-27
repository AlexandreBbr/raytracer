/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <iostream>

namespace raytracer {
    class Parser {
        public:
            Parser();
            ~Parser();
            bool parseFile(std::string const &filename);

        protected:
        private:
    };
};

#endif /* !PARSER_HPP_ */
