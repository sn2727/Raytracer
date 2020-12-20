#include <rt/materials/combine.h>

namespace rt {

CombineMaterial::CombineMaterial()
{

}

void CombineMaterial::add(Material* m, float w) {
    materials.push_back(std::pair<Material*, float>(m, w));
}

RGBColor CombineMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    RGBColor reflectance = RGBColor::rep(0);
    for (std::pair<Material*, float> pair : materials) {
        reflectance = reflectance + pair.first->getReflectance(texPoint, normal, outDir, inDir) * pair.second;
    }
    return reflectance;
}

RGBColor CombineMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    RGBColor emission = RGBColor::rep(0);
    for (std::pair<Material*, float> pair : materials) {
        emission = emission + pair.first->getEmission(texPoint, normal, outDir) * pair.second;
    }
    return emission;
}

Material::SampleReflectance CombineMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    for (std::pair<Material*, float> pair : materials) {
        if (pair.first->useSampling() == SAMPLING_ALL) {
            return pair.first->getSampleReflectance(texPoint, normal, outDir);
        }
    }
    return SampleReflectance{Vector(1,0,0), RGBColor::rep(0)};

}

Material::Sampling CombineMaterial::useSampling() const {
    return SAMPLING_SECONDARY;
}

}