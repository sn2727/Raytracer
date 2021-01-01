#include <rt/textures/checkerboard.h>

namespace rt {

CheckerboardTexture::CheckerboardTexture(const RGBColor& white, const RGBColor& black)
{
    this -> white = white;
    this -> black = black;
}

RGBColor CheckerboardTexture::getColor(const Point& coord) {
    float x = coord.x;
    float y = coord.y;
    float z = coord.z;
    if (x<0) { while (x<0) x++;}
    if (y<0) { while (y<0) y++;}
    if (z<0) { while (z<0) z++;}
    
    int xb = int(x*2) % 2;
    int yb = int(y*2) % 2;
    int zb = int(z*2) % 2;
    if ((xb+yb+zb) % 2 == 0) return white;
    return black;
}

RGBColor CheckerboardTexture::getColorDX(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor CheckerboardTexture::getColorDY(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

}