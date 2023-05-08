#include <SFML/Graphics.hpp>
#include <cmath>

struct Sphere {
    sf::Vector3f center;
    float radius;
    sf::Color color;
};

sf::Vector3f rotateVector(sf::Vector3f rayDirection, sf::Vector3f cameraDirection, sf::Vector3f cameraPosition)
{
    float angle = std::acos(cameraDirection.x * rayDirection.x + cameraDirection.y * rayDirection.y + cameraDirection.z * rayDirection.z);
    sf::Vector3f axis = sf::Vector3f::cross(cameraDirection, rayDirection);
    sf::Vector3f rotatedVector = rayDirection * std::cos(angle) + sf::Vector3f::cross(axis, rayDirection) * std::sin(angle) + axis * (1 - std::cos(angle));
    return rotatedVector;
}

sf::Color traceRay(const sf::Vector3f& rayOrigin, const sf::Vector3f& rayDirection, const std::vector<Sphere>& spheres)
{
    float tMin = INFINITY;
    const Sphere* hitSphere = nullptr;

    for (const Sphere& sphere : spheres) {
        float t = 0;

        sf::Vector3f L = sphere.center - rayOrigin;
        float tca = L.x * rayDirection.x + L.y * rayDirection.y + L.z * rayDirection.z;
        float d2 = L.x * L.x + L.y * L.y + L.z * L.z - tca * tca;

        if (d2 > sphere.radius * sphere.radius)
            continue;

        float thc = sqrt(sphere.radius * sphere.radius - d2);
        float t0 = tca - thc;
        float t1 = tca + thc;

        if (t0 > t1)
            std::swap(t0, t1);

        if (t0 < 0)
            t0 = t1;

        if (t0 < 0)
            continue;

        if (t0 < tMin) {
            tMin = t0;
            hitSphere = &sphere;
        }
    }

    if (hitSphere)
        return hitSphere->color;

    return sf::Color::Black; // Couleur de fond si aucun objet n'est touché
}

int main()
{


    return 0;
}