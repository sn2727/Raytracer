#include <rt/lights/arealight.h>

#include <core/color.h>

namespace rt {

LightHit AreaLight::getLightHit(const Point& p) const {
    Vector dir = source->sample().point - p;
    float distance = dir.length();
    if (fabs(distance) < epsilon) {
        return LightHit{dir, distance, Vector(0,0,0)};
    }
    return {dir, distance, dir.normalize()};
}

RGBColor AreaLight::getIntensity(const LightHit& irr) const {
    RGBColor color = RGBColor::rep(0);
    Solid::Sample s = source->sample();
    return source -> material -> getEmission(s.point, s.normal, Vector(1,0,0));
    /*for (int i = 0; i<SAMPLES; i++) {
        Solid::Sample s = source->sample();
        color = color + source->material->getEmission(s.point, s.normal, Vector(1,0,0));
    }
    return color/SAMPLES;*/
}

AreaLight::AreaLight(Solid* source)
{
    this -> source = source;
}

}