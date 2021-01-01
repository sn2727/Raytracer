#include <rt/coordmappers/world.h>

namespace rt {

Point WorldMapper::getCoords(const Intersection& hit) const {
    Point hitP = hit.local();
    return Point(hitP.x*scale.x, hitP.y*scale.y, hitP.z*scale.z);
}

WorldMapper::WorldMapper()
{
    this -> scale = Vector(1,1,1);
}

WorldMapper::WorldMapper(const Vector& scale)
{
    this -> scale = scale;
}

}