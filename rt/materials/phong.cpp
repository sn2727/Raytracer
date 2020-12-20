#include <rt/materials/phong.h>
#include <cmath>

namespace rt {

PhongMaterial::PhongMaterial(Texture* specular, float exponent)
{
    this -> specular = specular;
    this -> exponent = exponent;
}

RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    return (((exponent+1)/(2*pi))*specular->getColor(texPoint) * std::pow(dot(reflect(inDir,normal),outDir), exponent) *dot(inDir, normal)).clamp();
}

RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor::rep(0);
}

Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	UNREACHABLE;
}

Material::Sampling PhongMaterial::useSampling() const {
	return SAMPLING_NOT_NEEDED;
}

}