#include <rt/coordmappers/plane.h>

namespace rt {

PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2) {
    this -> e1 = e1;
    this -> e2 = e2;
}

Point PlaneCoordMapper::getCoords(const Intersection& hit) const {
    Point hitP(hit.local());
    Vector v(hitP.x*e1 + hitP.y*e2);
    return Point(v.x, v.y, v.z);
}

}