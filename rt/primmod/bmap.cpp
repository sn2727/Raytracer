#include <rt/primmod/bmap.h>
#include <core/assert.h>

namespace rt {

BumpMapper::BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1, const Point& bv2, const Point& bv3, float vscale)
{
    this -> base = base;
    this -> bumpmap = bumpmap;
    this -> bv1 = bv1;
    this -> bv2 = bv2;
    this -> bv3 = bv3;
    this -> vscale = 1;
    this -> material = nullptr;
    this -> coordMapper = new WorldMapper();
}

BBox BumpMapper::getBounds() const {
    return base -> getBounds();
}

// TODO: A full implementation has to make use of the coord mappers as well!
Intersection BumpMapper::intersect(const Ray& ray, float previousBestDistance) const {
    Intersection intsec = base -> intersect(ray, previousBestDistance);
    if (!intsec) return Intersection::failure();
    Point texPoint2 = coordMapper->getCoords(intsec);
    Point texPoint = intsec.local();
    Vector normal = base->normal;
    float u = texPoint.x;
    float v = texPoint.y;
    Vector dx(bumpmap->getColorDX(texPoint).r, bumpmap->getColorDX(texPoint).g, bumpmap->getColorDX(texPoint).b);
    Vector dy(bumpmap->getColorDY(texPoint).r, bumpmap->getColorDY(texPoint).g, bumpmap->getColorDY(texPoint).b);
    Vector Ov = bv1*v - texPoint;
    Vector Ou = bv2*u - texPoint;
    Vector OvN = cross(normal, Vector(Ov.x, Ov.y, Ov.z));
    Vector OuN = cross(normal, Vector(Ou.x, Ou.y, Ou.z));
    Vector checkNormal = cross(Vector(Ou.x, Ou.y, Ou.z), Vector(Ov.x, Ov.y, Ov.z));
    Vector D = Vector(dx.x*OvN.x, dx.y*OvN.y, dx.z*OvN.z) - Vector(dy.x*OuN.x, dy.y*OuN.y, dy.z*OuN.z);
    Vector normalP = (base->normal + vscale*D);
    
    return Intersection(intsec.distance, ray, intsec.solid, normalP, intsec.local());

}

void BumpMapper::setMaterial(Material* m) {
    this -> material = m;
}

void BumpMapper::setCoordMapper(CoordMapper* cm) {
    this -> coordMapper = cm;
}

}