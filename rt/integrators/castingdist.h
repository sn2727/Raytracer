#ifndef CG1RAYTRACER_INTEGRATORS_CASTINGDIST_HEADER
#define CG1RAYTRACER_INTEGRATORS_CASTINGDIST_HEADER

#include <rt/integrators/integrator.h>
#include <rt/ray.h>
#include <rt/intersection.h>
#include <rt/world.h>
#include <core/color.h>


namespace rt {

class RayCastingDistIntegrator : public Integrator {
public:
    RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist, const RGBColor& farColor, float farDist);
    virtual RGBColor getRadiance(const Ray& ray) const;
    float farDist;
    float nearDist;
    RGBColor nearColor;
    RGBColor farColor;  
};
 
}

#endif