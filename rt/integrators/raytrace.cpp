#include <rt/integrators/raytrace.h>


namespace rt {

RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {

    RGBColor radiance = RGBColor::rep(0);
    Intersection intsec = world -> scene -> intersect(ray);
    if (!intsec) return radiance;
    Point texPoint = intsec.solid->texMapper->getCoords(intsec);
    Material* material = intsec.solid->material;
    Vector outDir(-intsec.ray.d);
    outDir = outDir.normalize();
    Vector normal(intsec.normal());
    normal = normal.normalize();
    Point hit = intsec.hitPoint();
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
 
    return (radiance + material->getEmission(texPoint, normal, outDir)).clamp();
}

}