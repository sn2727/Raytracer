#include <rt/solids/infiniteplane.h>

namespace rt {

InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material)
{
    this -> origin = origin;
    this -> normal = normal.normalize();
    if (texMapper == nullptr) 
    this -> texMapper = new WorldMapper();
    else
    this -> texMapper = texMapper;
    this -> material = material;
    
}

BBox InfinitePlane::getBounds() const {
    return BBox::full();
}

Intersection InfinitePlane::intersect(const Ray& ray, float previousBestDistance) const {
    float denom = dot(normal, ray.d);
    if (fabs(denom) > epsilon) {
        float t = (dot(origin - ray.o, normal))/denom;
        if (t >= epsilon && t < previousBestDistance) return Intersection(t, ray, this, normal, ray.getPoint(t));
    }

    return Intersection::failure();
}

Solid::Sample InfinitePlane::sample() const {
    return {origin, normal};
}

float InfinitePlane::getArea() const {
    return FLT_MAX;
}

}
