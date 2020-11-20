#include <rt/integrators/casting.h>
#include <rt/world.h>

namespace rt {

RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const {
    Intersection intsec = this->world->scene->intersect(ray);
    return (RGBColor::rep(dot(ray.d, intsec.normal())));
}

}
