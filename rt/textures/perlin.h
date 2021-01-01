#ifndef CG1RAYTRACER_TEXTURES_PERLIN_HEADER
#define CG1RAYTRACER_TEXTURES_PERLIN_HEADER

#include <rt/textures/texture.h>
#include <core/scalar.h>

namespace rt {

class PerlinTexture : public Texture {
public:
    PerlinTexture(const RGBColor& white, const RGBColor& black);
    void addOctave(float amplitude, float frequency);
    virtual RGBColor getColor(const Point& coord);
    virtual RGBColor getColorDX(const Point& coord);
    virtual RGBColor getColorDY(const Point& coord);
    RGBColor getBlankColor(const Point& coord);
    RGBColor white;
    RGBColor black;
    float frequency;
    float octaves;
    float amplitude;
};

}

#endif