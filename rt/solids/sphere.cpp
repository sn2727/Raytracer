#include <rt/solids/sphere.h>

namespace rt {

Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material)
{
    this -> center = center;
    this -> radius = radius;
    this -> texMapper = texMapper;
    this -> material = material;
    this -> radius2 = radius * radius;
}

BBox Sphere::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const {
    float t0, t1; 

    Vector L = ray.o - center; 
    float a = dot(ray.d, ray.d); 
    float b = 2 * dot(ray.d,L); 
    float c = dot(L,L) - radius2; 
    if (!solveQuadratic(a, b, c, t0, t1)) return Intersection::failure(); 

    if (t0 > t1) std::swap(t0, t1); 
 
    if (t0 < 0) { 
        t0 = t1; // if t0 is negative, use t1 instead 
        if (t0 < 0) return Intersection::failure(); // both are negative 
    } 
 
    float t = t0; 
    
    Point hitPoint = ray.getPoint(t);
    Vector hitNormal = (hitPoint - center).normalize();
    return Intersection(t, ray, this, hitNormal, hitPoint);
}

Solid::Sample Sphere::sample() const {
	NOT_IMPLEMENTED;
}

float Sphere::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
}

bool Sphere::solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1) const {
    float discr = b * b - 4 * a * c; 
    if (discr < 0) return false; 
    else if (discr == 0) x0 = x1 = - 0.5f * b / a; 
    else { 
        float q = (b > 0) ? 
            -0.5f * (b + sqrt(discr)) : 
            -0.5f * (b - sqrt(discr)); 
        x0 = q / a; 
        x1 = c / q; 
    } 
    if (x0 > x1) std::swap(x0, x1); 
 
    return true; 
}

}
