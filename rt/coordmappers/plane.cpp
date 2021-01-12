#include <rt/coordmappers/plane.h>

namespace rt {

PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2) {
    this -> e1 = e1;
    this -> e2 = e2;
    this -> normal = cross(e1, e2).normalize();
    this -> origin = Point(0,0,0);
}

Point PlaneCoordMapper::getCoords(const Intersection& hit) const {
    Point hitP(hit.local());
    Vector v = hitP - origin;
    float dist = dot(v, normal);
    //projected point onto the plane
    Point proj = hitP - dist*normal; 
    //scaled by e1 and e2
    return Point(proj.x*e1.x*e2.x, proj.y*e1.y*e2.y, proj.z*e1.z*e2.z); 
    }
}