#include <rt/bbox.h>

namespace rt {

BBox BBox::empty() {
    BBox box(Point(1,1,1), Point(0,0,0));
    box.empty_ = true;
    return box;
}

BBox BBox::full() {
    return BBox(Point(-FLT_MAX, -FLT_MAX, -FLT_MAX), Point(FLT_MAX, FLT_MAX, FLT_MAX));
}


void BBox::extend(const Point& point) {
    if (empty_) {
        this -> min = point;
        this -> max = point;
        this -> empty_ = false;
    } else {
        Point newmin = rt::min(point, this -> min);
        Point newmax = rt::max(point, this -> max);
        this -> min = newmin;
        this -> max = newmax;
    }
}

bool BBox::overlaps(const BBox& bbox){
    if (empty_) {
        return false;
    }
    if (min.x > bbox.max.x && min.y > bbox.max.y && min.z > bbox.max.z) {
        return false;
    }
    if (max.x < bbox.min.x && max.y < bbox.min.y && max.z < bbox.min.z) {
        return false;
    }
    return true;
}

void BBox::extend(const BBox& bbox) {
    if (empty_) {
        this -> min = bbox.min;
        this -> max = bbox.max;
        this -> empty_ = false;
    } else {
        Point newmin = rt::min(bbox.min, this -> min);
        Point newmax = rt::max(bbox.max, this -> max);
        this -> min = newmin;
        this -> max = newmax;
    }
}

std::pair<float, float> BBox::intersect(const Ray& ray) const {
    Vector invdir(1/ray.d.x, 1/ray.d.y, 1/ray.d.z);
    
    float tmin, tmax, tymin, tymax, tzmin, tzmax; 

    Point bounds[2];
    bounds[0] = min;
    bounds[1] = max;

    int sign[3];
    sign[0] = (invdir.x < 0); 
    sign[1] = (invdir.y < 0); 
    sign[2] = (invdir.z < 0);

    tmin = (bounds[sign[0]].x - ray.o.x) * invdir.x; 
    tmax = (bounds[1-sign[0]].x - ray.o.x) * invdir.x; 
    tymin = (bounds[sign[1]].y - ray.o.y) * invdir.y; 
    tymax = (bounds[1-sign[1]].y - ray.o.y) * invdir.y; 
 
    if ((tmin > tymax) || (tymin > tmax)) 
        return std::make_pair(1,0);
    if (tymin > tmin) 
        tmin = tymin; 
    if (tymax < tmax) 
        tmax = tymax; 
 
    tzmin = (bounds[sign[2]].z - ray.o.z) * invdir.z; 
    tzmax = (bounds[1-sign[2]].z - ray.o.z) * invdir.z; 
 
    if ((tmin > tzmax) || (tzmin > tmax)) 
        return std::make_pair(1,0);
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
