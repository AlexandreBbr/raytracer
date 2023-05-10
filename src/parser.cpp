/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** parser
*/

#include "../include/Parser.hpp"
#include "libconfig.h++"

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
        this->parseCamera(root.lookup("camera"));
        this->parsePrimitives(root.lookup("primitives"));
        this->parseLights(root.lookup("lights"));
    }
    catch (const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
    }
    catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
    }
}

void raytracer::Parser::parseCamera(const libconfig::Setting &camera)
{
    try {
        const libconfig::Setting &resolution = camera.lookup("resolution");
        int width, height;
        resolution.lookupValue("width", width);
        resolution.lookupValue("height", height);
        std::cout << "width: " << width << std::endl;
        std::cout << "height: " << height << std::endl;

        const libconfig::Setting &position = camera.lookup("position");
        int x, y, z;
        position.lookupValue("x", x);
        position.lookupValue("y", y);
        position.lookupValue("z", z);
        std::cout << "x: " << x << std::endl;
        std::cout << "y: " << y << std::endl;
        std::cout << "z: " << z << std::endl;

        const libconfig::Setting &rotation = camera.lookup("rotation");
        int rx, ry, rz;
        rotation.lookupValue("x", rx);
        rotation.lookupValue("y", ry);
        rotation.lookupValue("z", rz);
        std::cout << "rx: " << rx << std::endl;
        std::cout << "ry: " << ry << std::endl;
        std::cout << "rz: " << rz << std::endl;

        float fov_value;
        camera.lookupValue("fov", fov_value);
        std::cout << "fov: " << fov_value << std::endl;
    }
    catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
    }
}

void raytracer::Parser::parsePrimitives(const libconfig::Setting &primitives)
{
    try {

        try {
            const libconfig::Setting &spheres = primitives.lookup("spheres");
            int count = spheres.getLength();

            for (int i = 0; i < count; i++) {
                try {
                    std::cout << "Sphere " << i << std::endl;
                    const libconfig::Setting &sphere = spheres[i];
                    int x, y, z;
                    sphere.lookupValue("x", x);
                    sphere.lookupValue("y", y);
                    sphere.lookupValue("z", z);
                    std::cout << "x: " << x << std::endl;
                    std::cout << "y: " << y << std::endl;
                    std::cout << "z: " << z << std::endl;

                    int rx, ry, rz;
                    sphere.lookupValue("rx", rx);
                    sphere.lookupValue("ry", ry);
                    sphere.lookupValue("rz", rz);
                    std::cout << "rx: " << rx << std::endl;
                    std::cout << "ry: " << ry << std::endl;
                    std::cout << "rz: " << rz << std::endl;

                    const libconfig::Setting &radius = sphere.lookup("color");
                    int cr, cg, cb;
                    sphere.lookupValue("r", cr);
                    sphere.lookupValue("g", cg);
                    sphere.lookupValue("b", cb);
                    std::cout << "r: " << cr << std::endl;
                    std::cout << "g: " << cg << std::endl;
                    std::cout << "b: " << cb << std::endl;
                }
                catch (const libconfig::SettingNotFoundException &nfex) { }
            }
        }
        catch(const libconfig::SettingNotFoundException &nfex) { }

        try {
            const libconfig::Setting &planes = primitives.lookup("planes");
            int count = planes.getLength();

            for (int i = 0; i < count; i++) {
                try {
                    std::cout << "Plane " << i << std::endl;
                    const libconfig::Setting &plane = planes[i];
                    int x, y, z;
                    plane.lookupValue("x", x);
                    plane.lookupValue("y", y);
                    plane.lookupValue("z", z);
                    std::cout << "x: " << x << std::endl;
                    std::cout << "y: " << y << std::endl;
                    std::cout << "z: " << z << std::endl;

                    int rx, ry, rz;
                    plane.lookupValue("rx", rx);
                    plane.lookupValue("ry", ry);
                    plane.lookupValue("rz", rz);
                    std::cout << "rx: " << rx << std::endl;
                    std::cout << "ry: " << ry << std::endl;
                    std::cout << "rz: " << rz << std::endl;

                    const libconfig::Setting &radius = plane.lookup("color");
                    int cr, cg, cb;
                    plane.lookupValue("r", cr);
                    plane.lookupValue("g", cg);
                    plane.lookupValue("b", cb);
                    std::cout << "r: " << cr << std::endl;
                    std::cout << "g: " << cg << std::endl;
                    std::cout << "b: " << cb << std::endl;
                }
                catch (const libconfig::SettingNotFoundException &nfex) { }
            }
        }
        catch(const libconfig::SettingNotFoundException &nfex) { }
    }
    catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
    }
}

void raytracer::Parser::parseLights(const libconfig::Setting &lights)
{
    try {
        try {
            float ambiantMultiplier;
            float diffuseMultiplier;
            lights.lookupValue("ambiant", ambiantMultiplier);
            lights.lookupValue("diffuse", diffuseMultiplier);
            std::cout << "ambiant: " << ambiantMultiplier << std::endl;
            std::cout << "diffuse: " << diffuseMultiplier << std::endl;

            try {
                const libconfig::Setting &points = lights.lookup("point");
                int count = points.getLength();

                for (int i = 0; i < count; i++) {
                    try {
                        std::cout << "Point " << i << std::endl;
                        const libconfig::Setting &point = points[i];
                        int x, y, z;
                        point.lookupValue("x", x);
                        point.lookupValue("y", y);
                        point.lookupValue("z", z);
                        std::cout << "x: " << x << std::endl;
                        std::cout << "y: " << y << std::endl;
                        std::cout << "z: " << z << std::endl;

                        try {
                            const libconfig::Setting &color = point.lookup("color");
                            int cr, cg, cb;
                            color.lookupValue("r", cr);
                            color.lookupValue("g", cg);
                            color.lookupValue("b", cb);
                            std::cout << "r: " << cr << std::endl;
                            std::cout << "g: " << cg << std::endl;
                            std::cout << "b: " << cb << std::endl;
                        }
                        catch (const libconfig::SettingNotFoundException &nfex) { }
                    }
                    catch (const libconfig::SettingNotFoundException &nfex) { }
                }
            }
            catch(const libconfig::SettingNotFoundException &nfex) { }

            try {
                const libconfig::Setting &directionals = lights.lookup("directional");
                int count = directionals.getLength();

                for (int i = 0; i < count; i++) {
                    try {
                        std::cout << "Directional " << i << std::endl;
                        const libconfig::Setting &point = directionals[i];
                        int x, y, z;
                        point.lookupValue("x", x);
                        point.lookupValue("y", y);
                        point.lookupValue("z", z);
                        std::cout << "x: " << x << std::endl;
                        std::cout << "y: " << y << std::endl;
                        std::cout << "z: " << z << std::endl;

                        int rx, ry, rz;
                        point.lookupValue("rx", rx);
                        point.lookupValue("ry", ry);
                        point.lookupValue("rz", rz);
                        std::cout << "rx: " << x << std::endl;
                        std::cout << "ry: " << y << std::endl;
                        std::cout << "rz: " << z << std::endl;

                        try {
                            const libconfig::Setting &color = point.lookup("color");
                            int cr, cg, cb;
                            color.lookupValue("r", cr);
                            color.lookupValue("g", cg);
                            color.lookupValue("b", cb);
                            std::cout << "r: " << cr << std::endl;
                            std::cout << "g: " << cg << std::endl;
                            std::cout << "b: " << cb << std::endl;
                        }
                        catch (const libconfig::SettingNotFoundException &nfex) { }
                    }
                    catch (const libconfig::SettingNotFoundException &nfex) { }
                }
            }
            catch(const libconfig::SettingNotFoundException &nfex) { }
        }
        catch (const libconfig::SettingNotFoundException &nfex) { }
    }
    catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
    }
}