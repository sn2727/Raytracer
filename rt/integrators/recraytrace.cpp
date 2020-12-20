#include <rt/integrators/recraytrace.h>

namespace rt {

RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const {
    int recDepth = 7;
    RGBColor radiance = RGBColor::rep(0);
    Intersection intsec = world -> scene -> intersect(ray);
    if (!intsec) return radiance;
    Material* material = intsec.solid->material;
    Vector outDir(-intsec.ray.d);
    outDir = outDir.normalize();
    Vector normal(intsec.normal());
    normal = normal.normalize();
    Point hit = intsec.hitPoint();
    if (material->useSampling() == Material::SAMPLING_NOT_NEEDED || 
        material->useSampling() == Material::SAMPLING_SECONDARY) {
        for (Light* lightsource : world->light) {
            LightHit lighthit = lightsource->getLightHit(hit);
            Ray shadowRay(hit, lighthit.direction);
            Intersection shadowIntsec = world -> scene -> intersect(shadowRay);
            if (shadowIntsec && shadowIntsec.distance < lighthit.distance && shadowIntsec.distance > BIAS) {
                continue;
            }
            Vector inDir(shadowRay.d);
            radiance = radiance +
                    lightsource->getIntensity(lighthit) *
                    material->getReflectance(hit, normal, outDir, inDir.normalize());
        }
    }
    if (material -> useSampling() == Material::SAMPLING_ALL ||
        material -> useSampling() == Material::SAMPLING_SECONDARY) {
        Material::SampleReflectance sample = material->getSampleReflectance(hit, normal, outDir);
        Ray secondary(hit, reflect(outDir, normal));
        radiance = getRadiance(secondary) * sample.reflectance;
    }
 
    return (radiance + material->getEmission(hit, normal, outDir)).clamp();
}

}