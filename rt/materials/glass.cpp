#include <rt/materials/glass.h>

namespace rt {

GlassMaterial::GlassMaterial(float eta)
{
    this -> eta = eta;
}

RGBColor GlassMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {

    float kr = 1;
    float cosi = clamp(-1.f, 1.f, dot(inDir, normal));
    float etai = 1;
    float etat = eta;
    if (cosi > 0) std::swap(etai, etat);
    float sint =  etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
    if (sint >= 1) {
        kr = 1;
    } else {
        float cost = sqrtf(std::max(0.f, 1 - sint * sint)); 
        cosi = fabsf(cosi); 
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
        kr = (Rs * Rs + Rp * Rp) / 2; 
    }
    return RGBColor::rep(kr);
}

float GlassMaterial::clamp(float lo, float hi, float v) const {
    assert( !(hi < lo) );
    return (v < lo) ? lo : (hi < v) ? hi : v;
}

RGBColor GlassMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor::rep(0);
}

Material::SampleReflectance GlassMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    Vector in = reflect(outDir, normal);
    return SampleReflectance{in, getReflectance(texPoint, normal, outDir, in)};
}

Material::Sampling GlassMaterial::useSampling() const {
    return SAMPLING_ALL;
}

}