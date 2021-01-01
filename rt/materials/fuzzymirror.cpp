#include <rt/materials/fuzzymirror.h>

namespace rt {

FuzzyMirrorMaterial::FuzzyMirrorMaterial(float eta, float kappa, float fuzzyangle)
{
    this -> eta = eta;
    this -> kappa = kappa;
    this -> fuzzyangle = fuzzyangle;
    this -> etasqr = eta*eta;
    this -> kappasqr = kappa * kappa;
}

RGBColor FuzzyMirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    float costheta = dot(inDir, normal);
    float costhetasqr = costheta*costheta;
    float rp = ((etasqr+kappasqr) * costhetasqr - 2*eta*costheta + 1) /
               ((etasqr+kappasqr) * costhetasqr + 2*eta*costheta + 1);
    float ro = ((etasqr+kappasqr) - 2*eta*costheta + costhetasqr) /
               ((etasqr+kappasqr) + 2*eta*costheta + costhetasqr);
    return RGBColor::rep(0.5f*(rp*rp+ro*ro));   
}

RGBColor FuzzyMirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor::rep(0);
}

Material::SampleReflectance FuzzyMirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    Vector in = reflect(outDir, normal);
    Disc disc(texPoint+in, in, fuzzyangle, nullptr, nullptr);
    Solid::Sample per = disc.sample();
    Vector perturbedIn = per.point - texPoint;
    return SampleReflectance{in, getReflectance(texPoint, normal, outDir, perturbedIn)};
}

Material::Sampling FuzzyMirrorMaterial::useSampling() const {
    return SAMPLING_ALL;
}

}
