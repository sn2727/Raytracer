#include <rt/solids/triangle.h>

namespace rt {

Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material)
{
    /* TODO */
}

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material)
{   
    this -> material = material;
    this -> texMapper = texMapper;
    this -> v1 = v1;
    this -> v2 = v2;
    this -> v3 = v3;
    Vector v1v2 = v2 - v1; 
    Vector v1v3 = v3 - v1; 
    this -> normal = cross(v1v2,v1v3);
    this -> area = 0.5f * normal.length();
    this -> d = dot(normal, Vector(v1.x,v1.y,v1.z));
}

BBox Triangle::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Triangle::intersect(const Ray& ray, float previousBestDistance) const {
       
    float NdotRayDirection = dot(normal, ray.d); 
    if (fabs(NdotRayDirection) < epsilon)
        return Intersection::failure(); // parallel so they don't intersect  
 
    float t = (dot(normal, Vector(ray.o.x,ray.o.y,ray.o.z)) + d) / NdotRayDirection; 

    if (t < epsilon || previousBestDistance <= t) return Intersection::failure(); // the triangle is behind 
    
    Point hit = ray.getPoint(t);
    Vector P = Vector(hit.x, hit.y, hit.z); 
 
    Vector C; // vector perpendicular to triangle's plane 
 
    // edge 1
    Vector edge1 = v2 - v1; 
    Vector vp1 = P - Vector(v1.x, v1.y, v1.z); 
    C = cross(edge1, vp1); 
    if (dot(normal, C) < 0) return Intersection::failure(); // P is on the right side 
 
    // edge 2
    Vector edge2 = v3 - v2; 
    Vector vp2 = P - Vector(v2.x,v2.y,v2.z); 
    C = cross(edge2, vp2); 
    if (dot(normal, C) < 0)  return Intersection::failure(); // P is on the right side 
 
    // edge 3
    Vector edge3 = v1 - v3; 
    Vector vp3 = P - Vector(v3.x,v3.y,v3.z); 
    C = cross(edge3, vp3); 
    if (dot(normal, C) < 0) return Intersection::failure(); // P is on the right side; 
 
    return Intersection(t, ray, this, normal, hit); 
}


Solid::Sample Triangle::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Triangle::getArea() const {
    return this -> area;
}

}