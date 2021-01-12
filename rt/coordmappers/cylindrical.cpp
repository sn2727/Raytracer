#include <rt/coordmappers/cylindrical.h>

namespace rt {

CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis)
{
    this -> longitudinalAxis = longitudinalAxis;
    this -> polarAxis = polarAxis;
    this -> origin = origin;
}

Point CylindricalCoordMapper::getCoords(const Intersection& hit) const {
    Point hitP(hit.local());

    //transform the cartesian coordinates into cylindrical
    float r2 = hitP.x*hitP.x + hitP.y*hitP.y;
    float theta = atan(hitP.y/hitP.x);
    float z = hitP.z;

    return Point(sqrt(r2)*polarAxis.length(), theta*longitudinalAxis.length(), z);
}

}