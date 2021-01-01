#include <rt/materials/flatmaterial.h>

namespace rt {

FlatMaterial::FlatMaterial(Texture* texture)
{
    this -> tex = texture;    
}

RGBColor FlatMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    return RGBColor::rep(0);
}

RGBColor FlatMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return tex->getColor(texPoint);
}

Material::SampleReflectance FlatMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    UNREACHABLE;
}

Material::Sampling FlatMaterial::useSampling() const {
    return SAMPLING_NOT_NEEDED;
}

}