#include <rt/solids/disc.h>

namespace rt {

Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material)
{
    /* TODO */
}

BBox Disc::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Disc::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Solid::Sample Disc::sample() const {
    NOT_IMPLEMENTED;
}

float Disc::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
}

}
