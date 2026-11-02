#ifndef OBJECTFACTORY_HPP_
#define OBJECTFACTORY_HPP_

#include "primitives/IPrimitive.hpp"

#include <functional>
#include <libconfig.h++>
#include <map>
#include <memory>
#include <string>

namespace raytracer {
    class ObjectFactory {
        public:
            using Creator = std::function<std::unique_ptr<primitives::IPrimitive>(
                const libconfig::Setting &, const math::Transform &, const primitives::Material &)>;

            ObjectFactory();

            void registerPrimitive(const std::string &name, Creator creator);
            bool knows(const std::string &name) const { return _creators.count(name) > 0; }
            std::unique_ptr<primitives::IPrimitive> create(const std::string &name,
                const libconfig::Setting &setting, const math::Transform &transform,
                const primitives::Material &material) const;

        private:
            std::map<std::string, Creator> _creators;
    };
}

#endif
