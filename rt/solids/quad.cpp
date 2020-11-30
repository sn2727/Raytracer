#include <rt/solids/quad.h>

namespace rt {

Quad::Quad(const Point& origin, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material)
{
    this -> origin = origin;
    this -> span1 = span1;
    this -> span2 = span2;
    this -> texMapper = texMapper;
    this -> material = material;
    this -> normal = cross(span1, span2);
    this -> area = normal.length();
    this -> plane = InfinitePlane(origin, normal, texMapper, material);
    this -> v1 = origin + span1;
    this -> v2 = v1 + span2;
    this -> v3 = origin + span2;
}

BBox Quad::getBounds() const {
    return BBox(min(min(origin, v1), min(v2,v3)), max(max(origin, v1), max(v2, v3)));
}

Intersection Quad::intersect(const Ray& ray, float previousBestDistance) const {
    Intersection intsec = plane.intersect(ray);
    if (!intsec) return Intersection::failure();
    float t = intsec.distance;
    if (t < epsilon || previousBestDistance <= t) return Intersection::failure();
   
    Point hit = ray.getPoint(t);
    Vector P = Vector(hit.x, hit.y, hit.z); 
 
    Vector C; // vector perpendicular to quads's plane 
 
    // edge 1
    Vector edge1 = v1 - origin; 
    Vector vp1 = P - Vector(origin.x, origin.y, origin.z); 
    C = cross(edge1, vp1); 
    if (dot(normal, C) < 0) return Intersection::failure(); // P is on the right side 
 
    // edge 2
    Vector edge2 = v2 - v1; 
    Vector vp2 = P - Vector(v1.x,v1.y,v1.z); 
    C = cross(edge2, vp2); 
    if (dot(normal, C) < 0)  return Intersection::failure(); // P is on the right side 
 
    // edge 3
    Vector edge3 = v3 - v2; 
    Vector vp3 = P - Vector(v2.x,v2.y,v2.z); 
    C = cross(edge3, vp3); 
    if (dot(normal, C) < 0)  return Intersection::failure(); // P is on the right side 
 
    // edge 4
    Vector edge4 = origin - v3; 
    Vector vp4 = P - Vector(v3.x,v3.y,v3.z); 
    C = cross(edge4, vp4); 
    if (dot(normal, C) < 0)  return Intersection::failure(); // P is on the right side 
 
    return Intersection(t, ray, this, normal.normalize(), hit);
}

Solid::Sample Quad::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Quad::getArea() const {
    return this -> area;
}

}
