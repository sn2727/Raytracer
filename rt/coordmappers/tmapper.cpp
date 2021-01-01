#include <rt/coordmappers/tmapper.h>

namespace rt {

TriangleMapper::TriangleMapper(Point ntv[3])
{
    this -> p0 = ntv[0];
    this -> p1 = ntv[1];
    this -> p2 = ntv[2];
}

TriangleMapper::TriangleMapper(const Point& tv0, const Point& tv1, const Point& tv2)
{
    this -> p0 = tv0;
    this -> p1 = tv1;
    this -> p2 = tv2;
}

Point TriangleMapper::getCoords(const Intersection& hit) const {
    return hit.local().x * p0 + hit.local().y * p1 + hit.local().z * p2;
}

}