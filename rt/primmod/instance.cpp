#include <rt/primmod/instance.h>

namespace rt {

Instance::Instance(Primitive* content)
{
    this -> archetype = content;
}

Primitive* Instance::content() {
    return archetype;
}

void Instance::reset() {
    this -> TMatrices.clear();
}

void Instance::translate(const Vector& t) {
    Matrix TMatrix = Matrix::identity();
    TMatrix[0][3] += t.x;
    TMatrix[1][3] += t.y;
    TMatrix[2][3] += t.z;
    TMatrices.push_back(TMatrix);
}

void Instance::rotate(const Vector& nnaxis, float angle) {
    float x = nnaxis.x;
    float y = nnaxis.y;
    float z = nnaxis.z;
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);
    Matrix TMatrix = Matrix::identity();
    TMatrix[0][0] = cosA+(x*x)*(1-cosA);
    TMatrix[0][1] = x*y*(1-cosA)-z*sinA;
    TMatrix[0][2] = x*z*(1-cosA)+y*sinA;
    TMatrix[1][0] = y*x*(1-cosA)+z*sinA;
    TMatrix[1][1] = cosA+y*y*(1-cosA);
    TMatrix[1][2] = y*z*(1-cosA)-x*sinA;
    TMatrix[2][0] = z*x*(1-cosA)-y*sinA;
    TMatrix[2][1] = z*y*(1-cosA)+x*sinA;
    TMatrix[2][2] = cosA + z*z*(1-cosA);
    TMatrices.push_back(TMatrix);
}

void Instance::scale(float f) {
    Matrix TMatrix = Matrix::identity();
    TMatrix[0][0] *= f;
    TMatrix[1][1] *= f;
    TMatrix[2][2] *= f;
    TMatrices.push_back(TMatrix);
}

void Instance::scale(const Vector& s) {
    Matrix TMatrix = Matrix::identity();
    TMatrix[0][0] *= s.x;
    TMatrix[1][1] *= s.y;
    TMatrix[2][2] *= s.z;
    TMatrices.push_back(TMatrix);
}

void Instance::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void Instance::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Instance::intersect(const Ray& ray, float previousBestDistance) const {
    Vector d = ray.d;
    Point o = ray.o;
    if (TMatrices.size()>0){
        for (int i = TMatrices.size() - 1; i >= 0; i--) {
            Matrix iM = TMatrices[i].invert();
            d = iM * d; 
            o = iM * o;    
        }
    }
    Ray invertedRay(o, d);
    Intersection intsec = this -> archetype->intersect(invertedRay, previousBestDistance);
    if (!intsec) {
        return Intersection::failure();
    }
    Vector normal = intsec.normal();
    for (Matrix m : TMatrices) {
        normal = m * normal;        
    }
    return Intersection(intsec.distance , ray, intsec.solid, normal, ray.getPoint(intsec.distance));
}

BBox Instance::getBounds() const {
    BBox box = archetype->getBounds();
    Point newmin = box.min;
    Point newmax = box.max;
    for (Matrix m : TMatrices) {
        newmin = m * newmin;
        newmax = m * newmax;
    }
    return BBox(newmin, newmax);
}

}