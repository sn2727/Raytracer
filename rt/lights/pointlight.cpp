#include <rt/lights/pointlight.h>
#include "light.h"
#include <core/vector.h>
#include <iostream>

namespace rt {

PointLight::PointLight(const Point& position, const RGBColor& intensity)
{
    this -> position = position;
    this -> intensity = intensity;
}

LightHit PointLight::getLightHit(const Point& p) const { 
    Vector dir = position - p;
    Vector dirN = dir.normalize();
    float distance = dir.length();   
    LightHit hit = {dir, distance, dirN};
    return hit;
}

RGBColor PointLight::getIntensity(const LightHit& irr) const {
    if (fabs(irr.distance) < epsilon) return intensity;
    return intensity/(irr.distance*irr.distance);
}

}
