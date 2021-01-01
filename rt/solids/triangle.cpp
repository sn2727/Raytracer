#include <rt/solids/triangle.h>

namespace rt {

Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material)
{
    Triangle(vertices[0], vertices[1], vertices[2], texMapper, material);
}

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material)
{   
    this -> material = material;
    if (texMapper == nullptr) 
    this -> texMapper = new WorldMapper();
    else
    this -> texMapper = texMapper;
    this -> v1 = v1;
    this -> v2 = v2;
    this -> v3 = v3;
    this -> edge1 = v2 - v1; 
    this -> edge2 = v3 - v1; 
    this -> normal = cross(edge1,edge2);
    this -> area = 0.5f * normal.length();
    this -> normal = this -> normal.normalize();
}

BBox Triangle::getBounds() const {
     return BBox(min(min(v1, v2), v3), max(max(v1,v2), v3));
}

//Moeller-Trumbore algorithm
Intersection Triangle::intersect(const Ray& ray, float previousBestDistance) const {
       
    Vector h = cross(ray.d, edge2);
    float a = dot(edge1, h);
    if (a > -epsilon && a < epsilon) return Intersection::failure(); //ray is parallel
    float f = 1.0f/a;
    Vector s = ray.o - v1;
    float u = f*dot(s,h);
    if (u < 0.0 || u > 1.0f) return Intersection::failure();
    Vector q = cross(s, edge1);
    float v = f*dot(ray.d, q);
    if (v < 0.0 || u+v > 1.0f) return Intersection::failure();
    float t = f*dot(edge2, q);
    if (t > epsilon && t < previousBestDistance) {
        return Intersection(t, ray, this, normal, Point(1-u-v, u, v));
    } else return Intersection::failure();

}


Solid::Sample Triangle::sample() const {
    float r1 = random();
    float r2 = random();
    float r1root = sqrt(r1);
    Point p = (1-r1root)*v1 + (r1root*(1-r2))*v2 + (r2*r1root)*v3;
    return {p, normal};
}

float Triangle::getArea() const {
    return this -> area;
}

}