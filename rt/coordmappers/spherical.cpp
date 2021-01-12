#include <rt/coordmappers/spherical.h>

namespace rt {
 

SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef)
{
    this -> origin = origin;
    this -> azimuthRef = azimuthRef;
    this -> zenith = zenith;
}

Point SphericalCoordMapper::getCoords(const Intersection& hit) const {
    Point hitP = hit.local();
    
    //convert cartesian coordinates into spherical
    float r2 = hitP.x*hitP.x + hitP.y*hitP.y + hitP.z*hitP.z;
    float r = sqrt(r2);
    float theta = atan(hitP.y/hitP.x);
    float phi = acos(hitP.z/r);

    return Point(r*azimuthRef.length(), theta*zenith.length(), phi);
}

}