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
    this -> edge1 = v2 - v1; 
    this -> edge2 = v3 - v1; 
    this -> normal = cross(edge1,edge2);
    this -> area = 0.5f * normal.length();
    this -> normal = this -> normal.normalize();
}

BBox Triangle::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
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
        return Intersection(t, ray, this, normal, ray.getPoint(t));
    } else return Intersection::failure();

}


Solid::Sample Triangle::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Triangle::getArea() const {
    return this -> area;
}

}