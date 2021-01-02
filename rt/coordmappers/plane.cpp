#include <rt/coordmappers/plane.h>

namespace rt {

PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2) {
    this -> e1 = e1.normalize();
    this -> e2 = e2.normalize();
}

Point PlaneCoordMapper::getCoords(const Intersection& hit) const {
    Point hitP(hit.local());
    float u = dot(e1, Vector(hitP.x, hitP.y, hitP.z));
    float v = dot(e1, Vector(hitP.x, hitP.y, hitP.z));
    return Point(u, v, e1.z);
}

}