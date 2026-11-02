#include "Parser.hpp"

#include <stdexcept>

namespace raytracer {
    using math::Vector3;

    static std::runtime_error error(const libconfig::Setting &s, const std::string &msg)
    {
        return std::runtime_error("line " + std::to_string(s.getSourceLine()) + ": " + msg);
    }

    static Vector3 readVector(const libconfig::Setting &parent, const char *name, Vector3 fallback = {})
    {
        if (!parent.exists(name))
            return fallback;
        const libconfig::Setting &s = parent[name];
        Vector3 v;
        if (!s.lookupValue("x", v.x) || !s.lookupValue("y", v.y) || !s.lookupValue("z", v.z))
            throw error(s, std::string("'") + name + "' needs x, y and z");
        return v;
    }

    static Vector3 readColor(const libconfig::Setting &parent, const char *name, Vector3 fallback)
    {
        if (!parent.exists(name))
            return fallback;
        const libconfig::Setting &s = parent[name];
        Vector3 c;
        if (!s.lookupValue("r", c.x) || !s.lookupValue("g", c.y) || !s.lookupValue("b", c.z))
            throw error(s, std::string("'") + name + "' needs r, g and b");
        return c / 255.0;
    }

    static primitives::Material readMaterial(const libconfig::Setting &s)
    {
        primitives::Material m;
        m.color = readColor(s, "color", m.color);
        if (s.exists("material")) {
            const libconfig::Setting &mat = s["material"];
            mat.lookupValue("reflection", m.reflection);
            mat.lookupValue("specular", m.specular);
            mat.lookupValue("shininess", m.shininess);
        }
        return m;
    }

    Scene Parser::parseFile(const std::string &filename) const
    {
        libconfig::Config cfg;
        Scene scene;

        cfg.setAutoConvert(true);
        try {
            cfg.readFile(filename.c_str());
        } catch (const libconfig::FileIOException &) {
            throw std::runtime_error("cannot read " + filename);
        } catch (const libconfig::ParseException &e) {
            throw std::runtime_error("line " + std::to_string(e.getLine()) + ": " + e.getError());
        }
        const libconfig::Setting &root = cfg.getRoot();
        if (!root.exists("camera"))
            throw std::runtime_error("missing 'camera' section");
        parseCamera(root["camera"], scene);
        if (root.exists("render"))
            parseRender(root["render"], scene);
        if (root.exists("primitives"))
            parsePrimitives(root["primitives"], scene);
        if (root.exists("lights"))
            parseLights(root["lights"], scene);
        return scene;
    }

    void Parser::parseCamera(const libconfig::Setting &camera, Scene &scene) const
    {
        int width = 800;
        int height = 600;
        double fov = 60;

        if (camera.exists("resolution")) {
            camera["resolution"].lookupValue("width", width);
            camera["resolution"].lookupValue("height", height);
        }
        camera.lookupValue("fov", fov);
        if (width <= 0 || height <= 0)
            throw error(camera, "resolution must be positive");
        if (fov <= 0 || fov >= 180)
            throw error(camera, "fov must be between 0 and 180");
        scene.camera = Camera(readVector(camera, "position"), readVector(camera, "rotation"), fov, width, height);
    }

    void Parser::parseRender(const libconfig::Setting &render, Scene &scene) const
    {
        render.lookupValue("antialiasing", scene.antialiasing);
        render.lookupValue("max_depth", scene.maxDepth);
        scene.background = readColor(render, "background", scene.background);
    }

    void Parser::parsePrimitives(const libconfig::Setting &primitives, Scene &scene) const
    {
        for (int i = 0; i < primitives.getLength(); i++) {
            const libconfig::Setting &list = primitives[i];
            std::string type = list.getName();
            if (!_factory.knows(type))
                throw error(list, "unknown primitive type '" + type + "'");
            for (int j = 0; j < list.getLength(); j++) {
                const libconfig::Setting &s = list[j];
                math::Transform transform(readVector(s, "position"), readVector(s, "rotation"));
                scene.primitives.push_back(_factory.create(type, s, transform, readMaterial(s)));
            }
        }
    }

    void Parser::parseLights(const libconfig::Setting &lights, Scene &scene) const
    {
        double ambient = 0.1;
        lights.lookupValue("ambient", ambient);
        scene.ambient = Vector3(1, 1, 1) * ambient;

        auto radiance = [](const libconfig::Setting &s) {
            double intensity = 1;
            s.lookupValue("intensity", intensity);
            return readColor(s, "color", {1, 1, 1}) * intensity;
        };
        if (lights.exists("directional")) {
            const libconfig::Setting &list = lights["directional"];
            for (int i = 0; i < list.getLength(); i++)
                scene.lights.push_back(std::make_unique<lights::DirectionalLight>(
                    readVector(list[i], "direction", {0, -1, 0}), radiance(list[i])));
        }
        if (lights.exists("point")) {
            const libconfig::Setting &list = lights["point"];
            for (int i = 0; i < list.getLength(); i++)
                scene.lights.push_back(std::make_unique<lights::PointLight>(
                    readVector(list[i], "position"), radiance(list[i])));
        }
    }
}
