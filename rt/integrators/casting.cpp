#include <rt/integrators/casting.h>
#include <rt/world.h>

namespace rt {

RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const {
    Intersection intsec = this->world->scene->intersect(ray);
    if (intsec) {
    return RGBColor::rep(dot(ray.d, intsec.normal())); 
    }
    return RGBColor::rep(0); //color to return when there is no intersection    
}

}
