#include <rt/solids/disc.h>

namespace rt {

Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material)
{
    this -> center = center;
    this -> normal = normal;
    this -> radius = radius;
    if (texMapper == nullptr) 
    this -> texMapper = new WorldMapper();
    else
    this -> texMapper = texMapper;
    this -> material = material;
    this -> radius2 = radius*radius;
    this -> plane = InfinitePlane(center, normal, texMapper, material);
    this -> area = pi * radius2;
}

BBox Disc::getBounds() const {
    float ex = radius*sqrt(1.0f - normal.x*normal.x);
    float ey = radius*sqrt(1.0f - normal.y*normal.y);
    float ez = radius*sqrt(1.0f - normal.z*normal.z);
    return BBox(center - Vector(ex,ey,ez), center + Vector(ex,ey,ez));
}

Intersection Disc::intersect(const Ray& ray, float previousBestDistance) const {
    Intersection intersec = plane.intersect(ray);
    if (intersec) {
        if (intersec.distance >= previousBestDistance) return Intersection::failure();
        Point hitPoint = intersec.hitPoint();
        Vector v = hitPoint - center;
        float dist2 = dot(v, v);
        if (dist2 > radius2) {
            return Intersection::failure();
        } else {
            return Intersection(intersec.distance, ray, this, intersec.normal(), intersec.hitPoint());
        }
    }

    return Intersection::failure();
}

Solid::Sample Disc::sample() const {
    Vector u(-normal.y, normal.x, 0);
    if (fabs(normal.x) < epsilon && fabs(normal.y) < epsilon)
        u = Vector(normal.z, 0, -normal.x);
    Vector v = cross(u, normal);  
    u = u.normalize() * radius;
    v = v.normalize() * radius;
    Point sample(FLT_MAX, FLT_MAX, FLT_MAX);
    bool outside = true;
    while (outside) {
        float r1 = 1-2*random();
        float r2 = 1-2*random();
        sample = center + r1*u + r1*v; 
        outside = (sample - center).length() > radius;
    }
    return {sample, normal};

}

float Disc::getArea() const {
    return area;
}

}
