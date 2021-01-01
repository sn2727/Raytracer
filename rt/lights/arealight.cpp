#include <rt/lights/arealight.h>

#include <core/color.h>

namespace rt {

LightHit AreaLight::getLightHit(const Point& p) const {
    return {Vector(1,0,0), 0, Vector(1,0,0)};
}

RGBColor AreaLight::getIntensity(const LightHit& irr) const {
    RGBColor color = RGBColor::rep(0);
    for (int i = 0; i<SAMPLES; i++) {
        Solid::Sample s = source->sample();
        color = color + source->material->getEmission(s.point, Vector(1,0,0), Vector(1,0,0));
    }
    return color/SAMPLES;
}

AreaLight::AreaLight(Solid* source)
{
    this -> source = source;
}

}