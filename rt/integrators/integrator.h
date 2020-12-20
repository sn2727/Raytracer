#ifndef CG1RAYTRACER_INTEGRATORS_INTEGRATOR_HEADER
#define CG1RAYTRACER_INTEGRATORS_INTEGRATOR_HEADER

#include <core/assert.h>
#include <core/color.h>
#include <rt/intersection.h>
#include <rt/materials/material.h>
#include <rt/lights/light.h>
#include <rt/world.h>
#include <rt/solids/solid.h>

namespace rt {

class World;
class Ray;

class Integrator {
public:
    const float BIAS = 0.00001f;
    Integrator(World* world) : world(world) {}
    virtual RGBColor getRadiance(const Ray& ray) const = 0;
protected:
    World* world;
};

}

#endif