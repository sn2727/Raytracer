#include <rt/lights/spotlight.h>
#include <iostream>

namespace rt {

SpotLight::SpotLight(const Point& position, const Vector& direction, float angle, float power, const RGBColor& intensity)
{
    this -> position = position;
    this -> direction = -direction;
    this -> angle = angle;
    this -> power = power;
    this -> intensity = intensity;
}

RGBColor SpotLight::getIntensity(const LightHit& irr) const {
    float ang = dot(direction, irr.direction);
    if (ang >= angle) {
        return RGBColor::rep(0);
    }
    return intensity/(irr.distance*irr.distance);
}

}
