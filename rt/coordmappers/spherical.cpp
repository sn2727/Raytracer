#include <rt/coordmappers/spherical.h>

namespace rt {
 

SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef)
{
    this -> origin = origin;
}

Point SphericalCoordMapper::getCoords(const Intersection& hit) const {
   Point hitPoint = hit.hitPoint();
   float theta = atan2(hitPoint.x, hitPoint.z);
   float radius = (hitPoint - origin).length();
   float phi = acos(hitPoint.y/radius);
   float thetaU = theta/(2*pi);
   float u = 1 - (thetaU + 0.5f);
   float v = 1 - phi/pi;
   return Point(u, v, hitPoint.z);
}

}