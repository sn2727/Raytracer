#include <rt/coordmappers/plane.h>

namespace rt {

PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2) {
    this -> normal = cross(e1, e2);
    this -> p = Point(0,0,0);

}

Point PlaneCoordMapper::getCoords(const Intersection& hit) const {
    Point o(hit.local());
    Vector dir(hit.normal());
    
    float denom = dot(dir, normal);
    float t = 1;
    if (fabs(denom) > epsilon)
    float t = dot((p-o), normal)/denom; 
    return (o+t*dir);
}

}