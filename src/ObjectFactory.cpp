#include "ObjectFactory.hpp"
#include "primitives/Primitives.hpp"

#include <stdexcept>

namespace raytracer {
    using namespace primitives;

    static double require(const libconfig::Setting &s, const char *name)
    {
        double value = 0;
        if (!s.lookupValue(name, value))
            throw std::runtime_error("line " + std::to_string(s.getSourceLine()) + ": missing '" + name + "'");
        return value;
    }

    ObjectFactory::ObjectFactory()
    {
        registerPrimitive("spheres", [](const auto &s, const auto &t, const auto &m) {
            return std::make_unique<Sphere>(t, m, require(s, "radius"));
        });
        registerPrimitive("planes", [](const auto &, const auto &t, const auto &m) {
            return std::make_unique<Plane>(t, m);
        });
        registerPrimitive("cylinders", [](const auto &s, const auto &t, const auto &m) {
            return std::make_unique<Cylinder>(t, m, require(s, "radius"), require(s, "height"));
        });
        registerPrimitive("cones", [](const auto &s, const auto &t, const auto &m) {
            return std::make_unique<Cone>(t, m, require(s, "radius"), require(s, "height"));
        });
    }

    void ObjectFactory::registerPrimitive(const std::string &name, Creator creator)
    {
        _creators[name] = std::move(creator);
    }

    std::unique_ptr<IPrimitive> ObjectFactory::create(const std::string &name,
        const libconfig::Setting &setting, const math::Transform &transform, const Material &material) const
    {
        auto it = _creators.find(name);
        if (it == _creators.end())
            throw std::runtime_error("unknown primitive type '" + name + "'");
        return it->second(setting, transform, material);
    }
}
