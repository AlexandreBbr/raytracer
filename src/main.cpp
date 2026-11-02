#include "Parser.hpp"
#include "Renderer.hpp"

#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>

static int usage(const char *bin)
{
    std::cout << "USAGE: " << bin << " <scene.cfg> [-o output.png|output.ppm] [-j threads]\n";
    return 0;
}

int main(int ac, char **av)
{
    std::string scenePath;
    std::string output = "output.ppm";
    unsigned threads = std::max(1u, std::thread::hardware_concurrency());

    for (int i = 1; i < ac; i++) {
        if (!std::strcmp(av[i], "--help") || !std::strcmp(av[i], "-h"))
            return usage(av[0]);
        if (!std::strcmp(av[i], "-o") && i + 1 < ac)
            output = av[++i];
        else if (!std::strcmp(av[i], "-j") && i + 1 < ac)
            threads = static_cast<unsigned>(std::max(1, std::atoi(av[++i])));
        else
            scenePath = av[i];
    }
    if (scenePath.empty()) {
        usage(av[0]);
        return 84;
    }
    try {
        raytracer::Scene scene = raytracer::Parser().parseFile(scenePath);
        auto start = std::chrono::steady_clock::now();
        raytracer::Image image = raytracer::Renderer(scene).render(threads);
        std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
        image.save(output);
        std::cout << image.width << "x" << image.height << ", " << scene.primitives.size() << " objects, "
                  << threads << " threads: " << elapsed.count() << " s -> " << output << "\n";
    } catch (const std::exception &e) {
        std::cerr << scenePath << ": " << e.what() << "\n";
        return 84;
    }
    return 0;
}
