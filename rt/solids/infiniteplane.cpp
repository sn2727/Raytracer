#include <rt/solids/infiniteplane.h>

namespace rt {

InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material)
{
    /* TODO */
}

BBox InfinitePlane::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection InfinitePlane::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Solid::Sample InfinitePlane::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float InfinitePlane::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
}

}
