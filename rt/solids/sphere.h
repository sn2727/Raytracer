#ifndef CG1RAYTRACER_SOLIDS_SPHERE_HEADER
#define CG1RAYTRACER_SOLIDS_SPHERE_HEADER

#include <rt/solids/solid.h>

namespace rt {

class Sphere : public Solid {
public:
    Sphere() {}
    Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual Sample sample() const;
    virtual float getArea() const;
    bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1) const;
    Point center; 
    float radius;
    float radius2;
    float area;
};

}


#endif