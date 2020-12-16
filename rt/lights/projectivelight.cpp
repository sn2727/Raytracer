#include <rt/lights/projectivelight.h>
#include <core/vector.h>

namespace rt {

ProjectiveLight::ProjectiveLight(const Point& position, const RGBColor& intensity)
{
    this -> position = position;
    this -> intensity = intensity;
}

LightHit ProjectiveLight::getLightHit(const Point& p) const { 
    Vector dir = position - p;
    float distance = dir.length();   
    if (fabs(distance) < epsilon) {
        return LightHit{dir, distance, Vector(0,0,0)};
    }
    return LightHit{dir, distance, dir.normalize()};
}

RGBColor ProjectiveLight::getIntensity(const LightHit& irr) const {
    if (fabs(irr.distance) < epsilon) return intensity;
    return RGBColor(irr.direction.x, irr.direction.y, irr.direction.z)*intensity/(irr.distance*irr.distance);
}

}
