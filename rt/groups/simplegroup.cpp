#include <rt/groups/simplegroup.h>

namespace rt {

BBox SimpleGroup::getBounds() const {
    BBox box = BBox::empty();
    for (Primitive* primitive : this -> primitives) {
        box.extend(primitive->getBounds());
    }
    return box;
}

Intersection SimpleGroup::intersect( const Ray& ray, float previousBestDistance) const {
    Intersection bestIntsec = Intersection::failure();
    for (Primitive* primitive : this -> primitives) {
        Intersection intsec = primitive->intersect(ray, previousBestDistance);
        if (intsec.distance < bestIntsec.distance) {
            bestIntsec = intsec;
        }
    }

    return bestIntsec;
}

void SimpleGroup::rebuildIndex() {
    //do nothing
}

void SimpleGroup::add(Primitive* p) {
    this->primitives.push_back(p);
}

void SimpleGroup::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void SimpleGroup::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

}
