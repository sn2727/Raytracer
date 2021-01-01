#include <rt/solids/aabox.h>

namespace rt {

AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material)
{
    this -> corner1 = corner1;
    this -> corner2 = corner2;
    if (texMapper == nullptr) 
    this -> texMapper = new WorldMapper();
    else
    this -> texMapper = texMapper;
    this -> material = material;
}

BBox AABox::getBounds() const {
    return BBox(corner1, corner2);
}

Solid::Sample AABox::sample() const {
    int r = floor(random() * 6);
    switch (r)
    {
    case 0:
        return Quad(corner1, Point(corner1.x, corner2.y, corner1.z) - corner1, 
            Point(corner2.x, corner1.y, corner1.z) - corner1, nullptr, nullptr).sample();
    case 1:
        return Quad(corner1, Point(corner1.x, corner2.y, corner1.z) - corner1, 
            Point(corner1.x, corner1.y, corner2.z) - corner1, nullptr, nullptr).sample();
    case 2:
        return Quad(corner1, Point(corner1.x, corner1.y, corner2.z) - corner1, 
            Point(corner2.x, corner1.y, corner1.z) - corner1, nullptr, nullptr).sample();
    case 3:
        return Quad(corner2, Point(corner2.x, corner1.y, corner2.z) - corner2, 
            Point(corner1.x, corner2.y, corner2.z) - corner2, nullptr, nullptr).sample();
    case 4:
        return Quad(corner2, Point(corner2.x, corner2.y, corner1.z) - corner2, 
            Point(corner1.x, corner2.y, corner2.z) - corner2, nullptr, nullptr).sample();
    case 5:
        return Quad(corner2, Point(corner2.x, corner1.y, corner2.z) - corner2, 
            Point(corner1.x, corner2.y, corner2.z) - corner2, nullptr, nullptr).sample();
    default: 
        return Quad(corner2, Point(corner2.x, corner1.y, corner2.z) - corner2, 
            Point(corner2.x, corner2.y, corner2.z) - corner2, nullptr, nullptr).sample();
    }
}

float AABox::getArea() const {
    Vector x = Vector(corner2.x - corner1.x, 0, 0); 
        Vector y = Vector(0, corner2.y - corner1.y, 0);
        Vector z = Vector(0, 0, corner2.z - corner1.z);
        float areaX = cross(x,y).length();
        float areaY = cross(x,z).length();
        float areaZ = cross(y,z).length();
        return (2*areaX + 2*areaY + 2*areaZ);
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
