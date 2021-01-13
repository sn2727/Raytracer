#include <rt/materials/glass.h>

namespace rt {

GlassMaterial::GlassMaterial(float eta)
{
    this -> eta = eta;
}

RGBColor GlassMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {

    float cosi = clamp(-1.f, 1.f, dot(-inDir, normal));
    float etai = 1;
    float etat = eta;
    if (cosi > 0) std::swap(etai, etat);
    float sint =  etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
    if (sint >= 1) {
        return RGBColor::rep(1.f);
    } else {
        float cost = sqrtf(std::max(0.f, 1 - sint * sint)); 
        cosi = fabsf(cosi); 
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
        return RGBColor::rep((Rs * Rs + Rp * Rp) / 2); 
    }
}

float GlassMaterial::clamp(float lo, float hi, float v) const {
    assert( !(hi < lo) );
    return (v < lo) ? lo : (hi < v) ? hi : v;
}

RGBColor GlassMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor::rep(0);
}

Material::SampleReflectance GlassMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    Vector reflected = reflect(outDir, normal);
    Vector N = normal;
    Vector I = -outDir;
    float cosi = clamp(-1, 1, dot(I, N)); 
    float etai = 1, etat = eta; 
    Vector n = N; 
    if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n= -N; } 
    float eta = etai / etat; 
    float k = 1 - eta * eta * (1 - cosi * cosi); 
    if (k>=0) {
        Vector refracted = eta * I + (eta * cosi - sqrtf(k)) * n;
        return SampleReflectance{refracted, (RGBColor::rep(1.f)-getReflectance(texPoint, normal, outDir, refracted))/sqr(eta)};
        }
    return SampleReflectance{reflected, getReflectance(texPoint, normal, outDir, reflected)}; 

}

Material::Sampling GlassMaterial::useSampling() const {
    return SAMPLING_ALL;
}

}