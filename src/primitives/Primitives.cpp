#include "primitives/Primitives.hpp"

#include <cmath>
#include <initializer_list>

namespace raytracer::primitives {
    static bool hitDisc(const Ray &ray, double y, double radius, double tMin, double tMax, double &t)
    {
        if (std::abs(ray.direction.y) < 1e-12)
            return false;
        double tc = (y - ray.origin.y) / ray.direction.y;
        if (tc < tMin || tc > tMax)
            return false;
        Vector3 p = ray.at(tc);
        if (p.x * p.x + p.z * p.z > radius * radius)
            return false;
        t = tc;
        return true;
    }

    bool Sphere::intersectLocal(const Ray &ray, double tMin, double tMax, double &t, Vector3 &normal) const
    {
        double t0 = 0;
        double t1 = 0;

        if (!solveQuadratic(ray.direction.dot(ray.direction), 2 * ray.origin.dot(ray.direction),
                ray.origin.dot(ray.origin) - _radius * _radius, t0, t1))
            return false;
        t = (t0 >= tMin) ? t0 : t1;
        if (t < tMin || t > tMax)
            return false;
        normal = ray.at(t) / _radius;
        return true;
    }

    bool Plane::intersectLocal(const Ray &ray, double tMin, double tMax, double &t, Vector3 &normal) const
    {
        if (std::abs(ray.direction.y) < 1e-12)
            return false;
        t = -ray.origin.y / ray.direction.y;
        normal = {0, 1, 0};
        return t >= tMin && t <= tMax;
    }

    bool Cylinder::intersectLocal(const Ray &ray, double tMin, double tMax, double &t, Vector3 &normal) const
    {
        const Vector3 &o = ray.origin;
        const Vector3 &d = ray.direction;
        double best = tMax;
        bool found = false;
        double t0 = 0;
        double t1 = 0;

        if (solveQuadratic(d.x * d.x + d.z * d.z, 2 * (o.x * d.x + o.z * d.z),
                o.x * o.x + o.z * o.z - _radius * _radius, t0, t1)) {
            for (double root : {t0, t1}) {
                double y = o.y + root * d.y;
                if (root >= tMin && root < best && y >= 0 && y <= _height) {
                    Vector3 p = ray.at(root);
                    best = root;
                    normal = {p.x, 0, p.z};
                    found = true;
                    break;
                }
            }
        }
        for (double capY : {0.0, _height}) {
            double tc = 0;
            if (hitDisc(ray, capY, _radius, tMin, best, tc)) {
                best = tc;
                normal = {0, capY > 0 ? 1.0 : -1.0, 0};
                found = true;
            }
        }
        t = best;
        return found;
    }

    bool Cone::intersectLocal(const Ray &ray, double tMin, double tMax, double &t, Vector3 &normal) const
    {
        const Vector3 &o = ray.origin;
        const Vector3 &d = ray.direction;
        double k = (_radius / _height) * (_radius / _height);
        double h = _height - o.y;
        double best = tMax;
        bool found = false;
        double t0 = 0;
        double t1 = 0;

        if (solveQuadratic(d.x * d.x + d.z * d.z - k * d.y * d.y, 2 * (o.x * d.x + o.z * d.z + k * h * d.y),
                o.x * o.x + o.z * o.z - k * h * h, t0, t1)) {
            for (double root : {t0, t1}) {
                double y = o.y + root * d.y;
                if (root >= tMin && root < best && y >= 0 && y <= _height) {
                    Vector3 p = ray.at(root);
                    best = root;
                    normal = {p.x, k * (_height - p.y), p.z};
                    found = true;
                    break;
                }
            }
        }
        double tc = 0;
        if (hitDisc(ray, 0, _radius, tMin, best, tc)) {
            best = tc;
            normal = {0, -1, 0};
            found = true;
        }
        t = best;
        return found;
    }
}
