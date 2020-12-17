#include <rt/materials/phong.h>

namespace rt {

PhongMaterial::PhongMaterial(Texture* specular, float exponent)
{
    /* TODO */
}

RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	UNREACHABLE;
}

Material::Sampling PhongMaterial::useSampling() const {
	/* TODO */ NOT_IMPLEMENTED;
}

}