#ifndef CG1RAYTRACER_LIGHTS_AREALIGHT_HEADER
#define CG1RAYTRACER_LIGHTS_AREALIGHT_HEADER

#include <rt/lights/light.h>
#include <rt/materials/material.h>
#include <rt/solids/solid.h>

namespace rt {

class Solid;

class AreaLight : public Light {
public:
    AreaLight() {}
    AreaLight(Solid* source);
    virtual LightHit getLightHit(const Point& p) const;
    virtual RGBColor getIntensity(const LightHit& irr) const;
    Solid* source;
    const int SAMPLES = 10;
};

}

#endif
