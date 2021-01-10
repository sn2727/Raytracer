#include <rt/lights/arealight.h>

#include <core/color.h>

namespace rt {

LightHit AreaLight::getLightHit(const Point& p) const {
    Solid::Sample s = source->sample();
    Vector dir = s.point - p;
    float distance = dir.length();
    return {dir, distance, s.normal};
}

RGBColor AreaLight::getIntensity(const LightHit& irr) const {
    Solid::Sample s = source->sample();
    RGBColor c = source->material->getEmission(s.point, s.normal, Vector(1,0,0));
    return c.clamp();
}

AreaLight::AreaLight(Solid* source)
{
    this -> source = source;
}

}