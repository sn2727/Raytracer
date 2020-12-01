#include <rt/integrators/casting.h>
#include <rt/world.h>

namespace rt {

RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const {
    Intersection intsec = this->world->scene->intersect(ray);
    if (intsec) {
    return RGBColor::rep(std::max(-dot(ray.d, intsec.normal()), 0.0f)); 
    }
    return RGBColor::rep(0.0f); //color to return when there is no intersection    
}

}
