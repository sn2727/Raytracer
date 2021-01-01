#include <rt/materials/mirror.h>
#include <core/scalar.h>

namespace rt {

MirrorMaterial::MirrorMaterial(float eta, float kappa)
{
    this -> eta = eta;
    this -> etasqr = eta*eta;
    this -> kappa = kappa;
    this -> kappasqr = kappa*kappa;
}

RGBColor MirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    float costheta = dot(inDir, normal);
    float costhetasqr = costheta*costheta;
    float rp = ((etasqr+kappasqr) * costhetasqr - 2*eta*costheta + 1) /
               ((etasqr+kappasqr) * costhetasqr + 2*eta*costheta + 1);
    float ro = ((etasqr+kappasqr) - 2*eta*costheta + costhetasqr) /
               ((etasqr+kappasqr) + 2*eta*costheta + costhetasqr);
    return RGBColor::rep(0.5f*(rp*rp+ro*ro));           
}

RGBColor MirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor::rep(0);
}

Material::SampleReflectance MirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
   Vector in = reflect(outDir, normal);
   return SampleReflectance{in, getReflectance(texPoint, normal, outDir, in)};
}

Material::Sampling MirrorMaterial::useSampling() const {
    return SAMPLING_ALL;
}

}