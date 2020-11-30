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
    Vector invdir(1/ray.d.x, 1/ray.d.y, 1/ray.d.z);
    
    float tmin, tmax, tymin, tymax, tzmin, tzmax; 

    Point bounds[2];
    bounds[0] = corner1;
    bounds[1] = corner2;

    int sign[3];
    sign[0] = (invdir.x < 0); 
    sign[1] = (invdir.y < 0); 
    sign[2] = (invdir.z < 0);

    tmin = (bounds[sign[0]].x - ray.o.x) * invdir.x; 
    tmax = (bounds[1-sign[0]].x - ray.o.x) * invdir.x; 
    tymin = (bounds[sign[1]].y - ray.o.y) * invdir.y; 
    tymax = (bounds[1-sign[1]].y - ray.o.y) * invdir.y; 
 
    if ((tmin > tymax) || (tymin > tmax)) 
        return Intersection::failure(); 
    if (tymin > tmin) 
        tmin = tymin; 
    if (tymax < tmax) 
        tmax = tymax; 
 
    tzmin = (bounds[sign[2]].z - ray.o.z) * invdir.z; 
    tzmax = (bounds[1-sign[2]].z - ray.o.z) * invdir.z; 
 
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

    return Intersection(tmin, ray, this, normal, hitPoint); 
}

}
