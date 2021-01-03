#include <rt/integrators/recraytrace.h>

namespace rt {

RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const {
    RGBColor radiance = RGBColor::rep(0);
    Intersection intsec = world -> scene -> intersect(ray);
    if (!intsec) return radiance;
    Point texPoint = intsec.solid->texMapper->getCoords(intsec);
    //Point texPoint = intsec.hitPoint();
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
                    material->getReflectance(texPoint, normal, outDir, inDir.normalize());
        }
    }
    if (material -> useSampling() == Material::SAMPLING_ALL ||
        material -> useSampling() == Material::SAMPLING_SECONDARY) {
        Material::SampleReflectance sample = material->getSampleReflectance(texPoint, normal, outDir);
        Ray secondary(hit, sample.direction);
        radiance = getRecursiveRadiance(secondary) * sample.reflectance;
        recDepth = REC_DEPTH;
    }
    return (radiance + material->getEmission(texPoint, normal, outDir));
}

RGBColor RecursiveRayTracingIntegrator::getRecursiveRadiance(const Ray& ray) const {
    recDepth--;
    if (recDepth == 0) {
        recDepth = REC_DEPTH;
        return RGBColor::rep(1);
    }
    return getRadiance(ray);
}

}