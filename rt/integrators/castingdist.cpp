#include <rt/integrators/castingdist.h>
#include <rt/ray.h>
#include <rt/intersection.h>
#include <rt/world.h>
#include <cmath>

namespace rt {

RayCastingDistIntegrator::RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist, const RGBColor& farColor, float farDist)
    : Integrator(world)
{
    this -> world = world;
    this -> nearDist = nearDist;
    this -> farDist = farDist;
    this -> nearColor = nearColor;
    this -> farColor = farColor;
}

RGBColor RayCastingDistIntegrator::getRadiance(const Ray& ray) const {
    Intersection intsec = this->world->scene->intersect(ray);
    if (intsec) {
    float per = (intsec.distance - nearDist) / (farDist - nearDist);
    RGBColor color = nearColor + per * (farColor - nearColor);
    return color.clamp() * -dot(intsec.normal(), ray.d);
    }
    return RGBColor::rep(0);
}

}
