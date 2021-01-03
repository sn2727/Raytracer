#include <rt/coordmappers/cylindrical.h>

namespace rt {

CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis)
{
    this -> longitudinalAxis = longitudinalAxis;
    this -> polarAxis = polarAxis;
}

Point CylindricalCoordMapper::getCoords(const Intersection& hit) const {
    Point hitP(hit.local());
    Vector v(hitP.x * polarAxis + hitP.y*longitudinalAxis);
    return Point(v.x, v.y, v.z);
}

}