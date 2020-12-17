#include <rt/textures/constant.h>

namespace rt {

ConstantTexture::ConstantTexture()
{
    /* TODO */
}

ConstantTexture::ConstantTexture(const RGBColor& color)
{
    /* TODO */
}

RGBColor ConstantTexture::getColor(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor ConstantTexture::getColorDX(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor ConstantTexture::getColorDY(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

}