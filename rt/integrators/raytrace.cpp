#include <rt/integrators/raytrace.h>
#include <rt/lights/light.h>
#include <rt/world.h>
#include <rt/solids/solid.h>
#include <rt/intersection.h>
#include <rt/materials/material.h>

namespace rt {

RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {
    RGBColor radiance = RGBColor::rep(0);
    Intersection intsec = world -> scene -> intersect(ray);
    if (!intsec) return radiance;
    Material* material = intsec.solid->material;
    Vector outDir(-intsec.ray.d);
    Vector normal(intsec.normal());
    Point hit = intsec.hitPoint();
     for (Light* lightsource : world->light) {
        LightHit lighthit = lightsource->getLightHit(hit);
        Ray shadowRay(hit, lighthit.direction);
        Intersection shadowIntsec = world -> scene -> intersect(shadowRay);
        if (shadowIntsec && shadowIntsec.distance < lighthit.distance) {
            continue;
        }
        Vector inDir(shadowRay.d);
        radiance = radiance +
                lightsource->getIntensity(lighthit) *
                material->getReflectance(hit, normal, outDir, inDir);
    }
 
    return (radiance + material->getEmission(hit, normal, outDir)).clamp();
}

}