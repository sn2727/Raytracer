#include <rt/bbox.h>

namespace rt {

BBox BBox::empty() {
   return BBox(Point(1,1,1), Point(-1,-1,-1));
}

BBox BBox::full() {
    return BBox(Point(-FLT_MAX, -FLT_MAX, -FLT_MAX), Point(FLT_MAX, FLT_MAX, FLT_MAX));
}


void BBox::extend(const Point& point) {
    Point newmin = rt::min(point, this -> min);
    Point newmax = rt::max(point, this -> max);
    this -> min = newmin;
    this -> max = newmax;
}

void BBox::extend(const BBox& bbox) {
    Point newmin = rt::min(bbox.min, this -> min);
    Point newmax = rt::max(bbox.max, this -> max);
    this -> min = newmin;
    this -> max = newmax;
}

std::pair<float, float> BBox::intersect(const Ray& ray) const {
    float tmin = 0;
    float tmax = 0;
    if (fabs(ray.d.x) > epsilon){
    tmin = (min.x - ray.o.x) / ray.d.x; 
    tmax = (max.x - ray.o.x) / ray.d.x; 
    }

    float tymin = 0;
    float tymax = 0;
    if (fabs(ray.d.y) > epsilon) {
    tymin = (min.y - ray.o.y) / ray.d.y; 
    tymax = (max.y - ray.o.y) / ray.d.y; 
    }

    if (tymin > tmin) 
        tmin = tymin; 
 
    if (tymax < tmax) 
        tmax = tymax; 
 
    float tzmin = 0;
    float tzmax = 0;
    if (fabs(ray.d.z) > epsilon) {
    tzmin = (min.z - ray.o.z) / ray.d.z; 
    tzmax = (max.z - ray.o.z) / ray.d.z; 
    }

    if (tzmin > tmin) 
        tmin = tzmin; 
 
    if (tzmax < tmax) 
        tmax = tzmax; 

    return std::make_pair(tmin, tmax);
}

bool BBox::isUnbound() {
    return (max.x >= FLT_MAX || max.y >= FLT_MAX || max.z >= FLT_MAX);
}

}
