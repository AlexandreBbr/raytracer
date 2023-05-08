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
    int width = 1920;   // Largeur de la fenêtre
    int height = 1080;  // Hauteur de la fenêtre

    sf::RenderWindow window(sf::VideoMode(width, height), "SFML 3D");
        window.create(sf::VideoMode::getDesktopMode(), "SFML Fullscreen", sf::Style::Fullscreen);

    sf::Vector3f cameraPosition(0.0, -100.0, 20.0);  // Position de la caméra
    sf::Vector3f cameraDirection(0.f, 0.f, 0.f);  // Direction vers laquelle la caméra est orientée

    std::vector<Sphere> spheres;
    spheres.push_back({ { 60.0, 5.0, 40.0}, 25.0, sf::Color::Red });
    spheres[0].center = {60.0, 5.0, 40.0};
    spheres[0].radius = 25.0;
    spheres[0].color = sf::Color::Red;
    spheres.push_back({ { -40.0, 20.0, -10.0}, 35.0, sf::Color::Green });
    spheres[1].center = {-40.0, 20.0, -10.0};
    spheres[1].radius = 35.0;
    spheres[1].color = sf::Color::Green;
    // Ajoutez vos sphères à la liste
    sf::Color pixelColor;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Image image;
        image.create(width, height);

        for (int z = 0; z < height; z++) {
            for (int x = 0; x < width; x++) {
                // Convertir les coordonnées de l'écran en rayon dans l'espace 3D
                float normalizedX = (2.f * x - width) / width;
                float normalizedZ = (height - 2.f * z) / height;

                sf::Vector3f rayDirection(normalizedX, 1.f, normalizedZ);
//                rayDirection = sf::Vector3f::normalize(rayDirection);
                rayDirection = rayDirection / std::sqrt(rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y + rayDirection.z * rayDirection.z);
                //rayDirection = rotateVector(rayDirection, cameraDirection, cameraPosition);
                pixelColor = traceRay(cameraPosition, rayDirection, spheres);

                image.setPixel(x, z, pixelColor);
            }
        }

        sf::Texture texture;
        texture.loadFromImage(image);

        sf::Sprite sprite(texture);

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}