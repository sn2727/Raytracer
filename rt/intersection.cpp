#include <rt/intersection.h>

namespace rt {

Intersection::Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& local)
{
    this -> distance = distance;
    this -> ray = ray;
    this -> solid = solid;
    this -> normal_ = normal;
    this -> local_ = local;
    this -> intersects = true;
    this -> hitPoint_ = ray.getPoint(distance); 
}

Intersection::operator bool() {
    return this->intersects;
}

Intersection Intersection::failure() {
    Intersection intersec = Intersection();
    intersec.intersects = false;
    intersec.distance = FLT_MAX;
    return intersec;
}

Point Intersection::hitPoint() const {
    return this -> hitPoint_;
}

Vector Intersection::normal() const {
    return this -> normal_;
}

Point Intersection::local() const {
    return this -> local_;
}

}
