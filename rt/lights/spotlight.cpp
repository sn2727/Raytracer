#include <rt/lights/spotlight.h>

namespace rt {

SpotLight::SpotLight(const Point& position, const Vector& direction, float angle, float power, const RGBColor& intensity)
{
    this -> position = position;
    this -> direction = direction;
    this -> angle = angle;
    this -> power = power;
    this -> intensity = intensity;
}

RGBColor SpotLight::getIntensity(const LightHit& irr) const {
    if (dot(direction.normalize(), irr.direction.normalize()) >= angle) {
        return RGBColor::rep(0);
    }
    return intensity * power;
}

}
