#include <rt/materials/flatmaterial.h>

namespace rt {

FlatMaterial::FlatMaterial(Texture* texture)
{
    /* TODO */
}

RGBColor FlatMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor FlatMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Material::SampleReflectance FlatMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    UNREACHABLE;
}

Material::Sampling FlatMaterial::useSampling() const {
    /* TODO */ NOT_IMPLEMENTED;
}

}