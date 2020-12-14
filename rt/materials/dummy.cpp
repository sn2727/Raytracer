#include <rt/materials/dummy.h>
#include <core/assert.h>
#include <cmath>

namespace rt {

DummyMaterial::DummyMaterial() {
    this -> fr = 1;
}

RGBColor DummyMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    return RGBColor::rep(fr  * dot(inDir.normalize(), normal)).clamp();
}

RGBColor DummyMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
   return RGBColor::rep(0);
}

Material::SampleReflectance DummyMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */ NOT_IMPLEMENTED;
}

}