#include <rt/solids/disc.h>

namespace rt {

Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material)
{
    this -> center = center;
    this -> normal = normal;
    this -> radius = radius;
    this -> texMapper = texMapper;
    this -> material = material;
    this -> radius2 = radius*radius;
    this -> plane = InfinitePlane(center, normal, texMapper, material);
}

BBox Disc::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Disc::intersect(const Ray& ray, float previousBestDistance) const {
    Intersection intersec = plane.intersect(ray);
    if (intersec) {
        if (intersec.distance >= previousBestDistance) return Intersection::failure();
        Point hitPoint = intersec.hitPoint();
        Vector v = hitPoint - center;
        float dist2 = dot(v, v);
        if (dist2 > radius2) {
            return Intersection::failure();
        } else {
            return Intersection(intersec.distance, ray, this, intersec.normal(), intersec.hitPoint());
        }
    }

    return Intersection::failure();
}

Solid::Sample Disc::sample() const {
    NOT_IMPLEMENTED;
}

float Disc::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
}

}
