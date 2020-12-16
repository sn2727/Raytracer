#include <rt/lights/directional.h>
#include <core/scalar.h>
#include <core/vector.h>

namespace rt {

DirectionalLight::DirectionalLight(const Vector& direction, const RGBColor& color)
{
    this -> direction = direction;
    this -> normal = direction.normalize();
    this -> color = color;
}

LightHit DirectionalLight::getLightHit(const Point& p) const {
    LightHit hit = {-direction, FLT_MAX, normal};
    return hit;
}

RGBColor DirectionalLight::getIntensity(const LightHit& irr) const {
    return color;
}

}
