#include <rt/solids/striangle.h>
#include <rt/intersection.h>

namespace rt {

SmoothTriangle::SmoothTriangle(Point vertices[3], Vector normals[3], CoordMapper* texMapper, Material* material)
{
    this -> triangle = new Triangle(vertices[0], vertices[1], vertices[2], texMapper, material);
    this -> n1 = normals[0];
    this -> n2 = normals[1];
    this -> n3 = normals[2];
}

SmoothTriangle::SmoothTriangle(const Point& v1, const Point& v2, const Point& v3, const Vector& n1, const Vector& n2, const Vector& n3, CoordMapper* texMapper, Material* material)
{
    this -> triangle = new Triangle(v1, v2, v3, texMapper, material);
    this -> n1 = n1;
    this -> n2 = n2;
    this -> n3 = n3;
}

Intersection SmoothTriangle::intersect(const Ray& ray, float previousBestDistance) const {
    Intersection intsec = triangle->intersect(ray, previousBestDistance);
    Point bary = intsec.local();
    Vector n(bary.x*n1 + bary.y*n2 + bary.z*n3);
    return Intersection(intsec.distance, intsec.ray, intsec.solid, n, intsec.local());
}

}