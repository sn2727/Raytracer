#include <rt/solids/aabox.h>

namespace rt {

AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material)
{
    this -> corner1 = corner1;
    this -> corner2 = corner2;
    this -> texMapper = texMapper;
    this -> material = material;
}

BBox AABox::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Solid::Sample AABox::sample() const {
    NOT_IMPLEMENTED;
}

float AABox::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection AABox::intersect(const Ray& ray, float previousBestDistance) const {
    float tmin = (corner1.x - ray.o.x) / ray.d.x; 
    float tmax = (corner2.x - ray.o.x) / ray.d.x; 
 
    if (tmin > tmax) std::swap(tmin, tmax); 
 
    float tymin = (corner1.y - ray.o.y) / ray.d.y; 
    float tymax = (corner2.y - ray.o.y) / ray.d.y; 
 
    if (tymin > tymax) std::swap(tymin, tymax); 
 
    if ((tmin > tymax) || (tymin > tmax)) 
        return Intersection::failure(); 
 
    if (tymin > tmin) 
        tmin = tymin; 
 
    if (tymax < tmax) 
        tmax = tymax; 
 
    float tzmin = (corner1.z - ray.o.z) / ray.d.z; 
    float tzmax = (corner2.z - ray.o.z) / ray.d.z; 
 
    if (tzmin > tzmax) std::swap(tzmin, tzmax); 
 
    if ((tmin > tzmax) || (tzmin > tmax)) 
        return Intersection::failure(); 
 
    if (tzmin > tmin) 
        tmin = tzmin; 
 
    if (tzmax < tmax) 
        tmax = tzmax; 
 
    if (previousBestDistance <= tmin || tmin < 0) return Intersection::failure();

    Point hitPoint = ray.getPoint(tmin);

    //calculate normal vector at hitpoint
    Point center((corner1.x+corner2.x)/2, (corner1.y+corner2.y)/2, (corner1.z+corner2.z)/2);
    Vector p = hitPoint - center;
    float dx = (fabs(corner1.x - corner2.x))/2;
    float dy = (fabs(corner1.y - corner2.y))/2;
    float dz = (fabs(corner1.z - corner2.z))/2;
    Vector normal((int)(p.x/dx),(int) (p.y/dy), (int) (p.z/dz));

    return Intersection(tmin, ray, this, normal.normalize(), hitPoint); 
}

}
