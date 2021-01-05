#include <rt/coordmappers/plane.h>

namespace rt {

PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2) {
    this -> e1 = e1;
    this -> e2 = e2;
    this -> normal = cross(e1, e2).normalize();
    this -> plane = InfinitePlane(Point(0,0,0), normal, nullptr, nullptr);
}

Point PlaneCoordMapper::getCoords(const Intersection& hit) const {
    Point hitP(hit.local());
    Intersection intsec1 = plane.intersect(Ray(hitP, -normal));
    Intersection intsec2 = plane.intersect(Ray(hitP, normal));
    if (intsec1) return intsec1.hitPoint();
    return intsec2.hitPoint();
}

}