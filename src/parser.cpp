/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** parser
*/

#include "../include/Parser.hpp"

raytracer::Parser::Parser()
{
}

raytracer::Parser::~Parser()
{
}

void raytracer::Parser::parseFile(const std::string &filename)
{
    try {
        libconfig::Config cfg;
        cfg.readFile(filename.c_str());

        const libconfig::Setting &root = cfg.getRoot();

        const libconfig::Setting &camera = root.lookup["camera"];
        int width;
        int height;
        camera.lookupValue("width", width);
        camera.lookupValue("height", height);

        const libconfig::Setting &spheres = root.lookup["sphere"];
        for (int i = 0; i < sphere.getLength(); i++) {
            const libconfig::Setting &sphere = spheres[i];
            int x, y, z, r;
            sphere.lookupValue("x", x);
            sphere.lookupValue("y", y);
            sphere.lookupValue("z", z);
            sphere.lookupValue("r", r); 
        }
    }
    catch (const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
    }
    catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
    }
}
