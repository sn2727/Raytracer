#ifndef CG1RAYTRACER_BBOX_HEADER
#define CG1RAYTRACER_BBOX_HEADER

#include <utility>
#include <core/point.h>
#include <core/vector.h>
#include <rt/solids/solid.h>


namespace rt {

class Ray;

class BBox {
public:
    Point min, max;

    BBox() {}
    BBox(const Point& min, const Point& max)
    {
        this -> min = min;
        this -> max = max;
    }

    static BBox empty();
    static BBox full();

    void extend(const Point& point);
    void extend(const BBox& bbox);

    Vector diagonal() const {
        return max-min;
    }

    float area() const {
        Vector x = Vector(max.x - min.x, 0, 0); 
        Vector y = Vector(0, max.y - min.y, 0);
        Vector z = Vector(0, 0, max.z - min.z);
        float areaX = cross(x,y).length();
        float areaY = cross(x,z).length();
        float areaZ = cross(y,z).length();
        return (2*areaX + 2*areaY + 2*areaZ);
    }

    std::pair<float, float> intersect(const Ray& ray) const;

    bool isUnbound();
};

}

#endif
