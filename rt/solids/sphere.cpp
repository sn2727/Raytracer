#include <rt/solids/sphere.h>

namespace rt {

Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material)
{
    /* TODO */
}

BBox Sphere::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Solid::Sample Sphere::sample() const {
	NOT_IMPLEMENTED;
}

float Sphere::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
}

}
