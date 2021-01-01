#ifndef CG1RAYTRACER_INTEGRATORS_RECURSIVERAYTRACING_HEADER
#define CG1RAYTRACER_INTEGRATORS_RECURSIVERAYTRACING_HEADER

#include <rt/integrators/integrator.h>

namespace rt {

class RecursiveRayTracingIntegrator : public Integrator {
public:
    RecursiveRayTracingIntegrator(World* world) : Integrator(world) {}
    virtual RGBColor getRadiance(const Ray& ray) const;
    mutable int recDepth;
    const int REC_DEPTH = 7;
    RGBColor RecursiveRayTracingIntegrator::getRecursiveRadiance(const Ray& ray) const;
};

}

#endif