/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-tristan.grosgeorge
** File description:
** Display
*/

#include "../include/Display.hpp"


raytracer::Display::Display()
{
    _width = 1920;   // Largeur de la fenêtre
    _height = 1080;  // Hauteur de la fenêtre
    _window = new sf::RenderWindow(sf::VideoMode(_width, _height), "Raytracer");
    _window->create(sf::VideoMode::getDesktopMode(), "SFML Fullscreen", sf::Style::Fullscreen);
    image.create(_width, _height);
    _texture = new sf::Texture();
    _sprite = new sf::Sprite();
    _pixels = new raytracer::Pixel;
    _isInit = false;
}

raytracer::Display::~Display()
{
    if (_isInit) {
        _texture->update((sf::Uint8*)_pixels, _window->getSize().x, _window->getSize().y, 0, 0);
    }
    delete _pixels;
    delete _sprite;
    delete _texture;
    _window->close();
    delete _window;
}

float distance(sf::Vector3f point1, sf::Vector3f point2) {
    // return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2) + pow(point2.z - point1.z, 2));
}

sf::Vector3f calculateRay(int x, int y, int windowWidth, int windowHeight, sf::Vector3f cameraPosition, sf::Vector3f cameraTarget) {
    // Calcul de la direction du rayon
    // float fov = 90.0f; // Champ de vision de la caméra en degrés
    // float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
    // float angle = tan(fov * 0.5f * 3.14159265f / 180.0f);
    // float pixelX = (2 * ((x + 0.5f) / windowWidth) - 1) * angle * aspectRatio;
    // float pixelY = (1 - 2 * ((y + 0.5f) / windowHeight)) * angle;
    // sf::Vector3f rayDirection(pixelX, pixelY, -1);
    // rayDirection = normalize(rayDirection);

    // // Rotation du rayon en fonction de la direction de la caméra
    // sf::Vector3f forward = normalize(cameraTarget - cameraPosition);
    // sf::Vector3f right = cross(sf::Vector3f(0, 1, 0), forward);
    // sf::Vector3f up = cross(forward, right);
    // sf::Matrix3f cameraMatrix(right.x, up.x, forward.x,
    //                           right.y, up.y, forward.y,
    //                           right.z, up.z, forward.z);
    // rayDirection = cameraMatrix * rayDirection;

    // return rayDirection;
}

void raytracer::Display::poolEvent()
{
    sf::Vector3f cameraPosition(0, 0, -5);

    // Position et rayon de la sphère
    sf::Vector3f spherePosition(0, 0, 0);
    float sphereRadius = 1;

    // Couleur de la sphère
    sf::Color sphereColor(255, 0, 0);
    while (_window->isOpen())
    {
        while (_window->pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed)
                return;
        }
        //  sf::Image image;
        // image.create(1920, 1080);

        // // Parcours de tous les pixels de l'image
        // for (int x = 0; x < 1920; x++) {
        //     for (int y = 0; y < 1080; y++) {
        //         // Calcul du rayon pour le pixel (x, y)
        //         sf::Vector3f ray = calculateRay(x, y, 1080, 1920, cameraPosition, cameraTarget);
        //         // Calcul des coefficients de l'équation du second degré pour l'intersection entre le rayon et la sphère
        //         float a = ray.x * ray.x + ray.y * ray.y + ray.z * ray.z;
        //         float b = 2 * (cameraPosition.x * ray.x + cameraPosition.y * ray.y + cameraPosition.z * ray.z - spherePosition.x * ray.x - spherePosition.y * ray.y - spherePosition.z * ray.z);
        //         float c = cameraPosition.x * cameraPosition.x + cameraPosition.y * cameraPosition.y + cameraPosition.z * cameraPosition.z + spherePosition.x * spherePosition.x + spherePosition.y * spherePosition.y + spherePosition.z * spherePosition.z - 2 * (cameraPosition.x * spherePosition.x + cameraPosition.y * spherePosition.y + cameraPosition.z * spherePosition.z) - sphereRadius * sphereRadius;

        //         // Calcul du discriminant de l'équation du second degré
        //         float discriminant = b * b - 4 * a * c;

        //         // Calcul de la distance entre l'observateur et l'intersection
        //         float distanceToIntersection = (-b - sqrt(discriminant)) / (2 * a);


        //         // Si le rayon intersecte la sphère
        // if (discriminant >= 0 && distanceToIntersection > 0) {
        //         sf::Vector3f intersection = cameraPosition + ray * distanceToIntersection;

        //                     // Dessin du pixel avec la couleur de la sphère
        //         image.setPixel(x, y, sphereColor);
        //         }
        //     }
        // }
        // _texture->loadFromImage(image);
        // _sprite->setTexture(*(_texture));

        // Affichage du sprite
        _window->draw(*(_sprite));

        // Affichage de la fenêtre
        _window->display();
    }
}

sf::Vector3f rotateVector(sf::Vector3f rayDirection, sf::Vector3f cameraDirection, sf::Vector3f cameraPosition)
{
    float angle = std::acos(cameraDirection.x * rayDirection.x + cameraDirection.y * rayDirection.y + cameraDirection.z * rayDirection.z);
    // sf::Vector3f axis = sf::Vector3f::cross(cameraDirection, rayDirection);
    // sf::Vector3f rotatedVector = rayDirection * std::cos(angle) + sf::Vector3f::cross(axis, rayDirection) * std::sin(angle) + axis * (1 - std::cos(angle));
    // return rotatedVector;
}

sf::Color traceRay(const sf::Vector3f& rayOrigin, const sf::Vector3f& rayDirection, const std::vector<raytracer::objects::Sphere>& spheres)
{
    float tMin = INFINITY;
    const raytracer::objects::Sphere* hitSphere = nullptr;

    for (const raytracer::objects::Sphere& sphere : spheres) {
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

sf::Vector3f raytracer::Display::normalize(int x, int z)
{
    float normalizedX = (2.f * x - _width) / _width;
    float normalizedZ = (_height - 2.f * z) / _height;
    sf::Vector3f rayDirection(normalizedX, 1.f, normalizedZ);
    rayDirection = rayDirection / std::sqrt(rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y + rayDirection.z * rayDirection.z);
    return rayDirection;
}

void raytracer::Display::launchScene()
{


    sf::Vector3f cameraPosition(0.0, -100.0, 20.0);  // Position de la caméra
    sf::Vector3f cameraDirection(0.f, 0.f, 0.f);  // Direction vers laquelle la caméra est orientée

    std::vector<raytracer::objects::Sphere> spheres;
    spheres.push_back({ { 60.0, 5.0, 40.0}, {0, 0.f, 0.f}, {0.f, 0.f, 0.f} });
    spheres[0].center = {60.0, 5.0, 40.0};
    spheres[0].radius = 25.0;
    spheres[0].color = sf::Color::Red;
    spheres.push_back({ { -40.0, 20.0, -10.0}, {0.f, 0.f, 0.f}, {0.f, 0.f, 0.f} });
    spheres[1].center = {-40.0, 20.0, -10.0};
    spheres[1].radius = 35.0;
    spheres[1].color = sf::Color::Green;
    // Ajoutez vos sphères à la liste
    sf::Color pixelColor;

    while ( _window->isOpen()) {
        while ( _window->pollEvent(_event)) {
            if (_event.type == sf::Event::Closed || (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape))
                 _window->close();
        }
        for (int z = 0; z < _height; z++) {
            for (int x = 0; x < _width; x++) {
                // Convertir les coordonnées de l'écran en rayon dans l'espace 3D
                _rayDirection = this->normalize(x, z);
                //rayDirection = rotateVector(rayDirection, cameraDirection, cameraPosition);
                pixelColor = traceRay(cameraPosition, _rayDirection, spheres);
                image.setPixel(x, z, pixelColor);
            }
        }
        _texture->loadFromImage(image);
        sf::Sprite sprite(*(_texture));
         _window->clear();
         _window->draw(sprite);
         _window->display();
    }
    return;
}
