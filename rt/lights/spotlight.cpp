#include <rt/lights/spotlight.h>
#include <iostream>
#include <cmath>

namespace rt {

SpotLight::SpotLight(const Point& position, const Vector& direction, float angle, float power, const RGBColor& intensity)
{
    this -> position = position;
    this -> direction = direction;
    float degangle = angle;
    this -> angle = degangle;
    this -> power = power;
    this -> intensity = intensity;
}

LightHit SpotLight::getLightHit(const Point& p) const { 
    Vector dir = position - p;
    float distance = dir.length();   
    if (fabs(distance) < epsilon) {
        return LightHit{dir, distance, Vector(0,0,0)};
    }
    return LightHit{dir, distance, dir.normalize()};
}

RGBColor SpotLight::getIntensity(const LightHit& irr) const {
    float cos = dot(-irr.direction, direction);
    if (fabs(irr.distance) < epsilon) return intensity;
    float ang = -dot(direction.normalize(), irr.direction.normalize());
    if (acos(ang) >= angle) {
        return RGBColor::rep(0);
    }
    return (intensity/(irr.distance*irr.distance)) * std::pow(cos, power);
}

}
