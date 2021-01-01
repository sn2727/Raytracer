#ifndef CG1RAYTRACER_TEXTURES_TEXTURE_HEADER
#define CG1RAYTRACER_TEXTURES_TEXTURE_HEADER

#include <core/color.h>
#include <core/point.h>
#include <core/interpolate.h>

namespace rt {

class Point;

class Texture {
public:
    virtual RGBColor getColor(const Point& coord) = 0;
    virtual RGBColor getColorDX(const Point& coord) = 0;
    virtual RGBColor getColorDY(const Point& coord) = 0;
    virtual ~Texture() {};
};

}

#endif