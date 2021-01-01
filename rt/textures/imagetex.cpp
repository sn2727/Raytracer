#include <rt/textures/imagetex.h>
#include <cmath>

namespace rt {

ImageTexture::ImageTexture()
{
    this -> image = Image();
    this -> bht = CLAMP;
    this -> it = NEAREST;
}

ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i)
{
    this -> image = Image();
    image.readPNG(filename);
    this -> bht = bh;
    this -> it = i;
}

ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i)
{
    this -> image = image;
    this -> bht = bh;
    this -> it = i;
}

RGBColor ImageTexture::getColor(const Point& coord) {
    int width = image.width();
    int height = image.height();
    float ndcx = coord.x / width;
    float ndcy = coord.y / height;
    switch (bht)
    {
    case CLAMP:
        float tu, tv;
        if (ndcx < 0) tu = 0; else if (ndcx > 1) tu = 1; else tu = ndcx;
        if (ndcy < 0) tv = 0; else if (ndcy > 1) tv = 1; else tv = ndcy;
        if (it == NEAREST) {
            return nearest(ndcx, ndcy); 
        } else {
            return bilinear(ndcx, ndcy, coord.z);
        }
        break;

    case MIRROR:
        if (ndcx < 0) {
            while (ndcx < 0) { 
                float tmp = ndcx - int(ndcx);
                ndcx -= 2*tmp; 
            } 
        }
        if (ndcx > 1) {
            while (ndcx > 1) {
                float tmp = ndcx - int(ndcx);
                ndcx -= 2*tmp; 
            }
        }
        if (ndcy < 0) {
            while (ndcy < 0) {
                float tmp = ndcy - int(ndcy);
                ndcy -= 2*tmp; 
            }
        }
        if (ndcy > 1) {
            while (ndcy > 1) {
                float tmp = ndcy - int(ndcy);
                ndcy -= 2*tmp; 
            } 
        }
        if (it == NEAREST) return nearest(ndcx, ndcy);
        return bilinear(ndcx, ndcy, coord.z);
        break;

    case REPEAT:
        if (ndcx < 0) {
            while (ndcx < 0) ndcx++; 
        }
        if (ndcx > 1) {
            while (ndcx > 1) ndcx--; 
        }
        if (ndcy < 0) {
            while (ndcy < 0) ndcy++; 
        }
        if (ndcy > 1) {
            while (ndcy > 1) ndcy--; 
        }
        if (it == NEAREST) return nearest(ndcx, ndcy);
        return bilinear(ndcx, ndcy, coord.z);
        break;
    default:
        return RGBColor::rep(0);
        break;
    }
}

RGBColor ImageTexture::nearest(float ndcx, float ndcy) {
    return image(round(ndcx*image.width()), round(ndcy*image.height()));
}

RGBColor ImageTexture::bilinear(float ndcx, float ndcy, float z) {
    float width = image.width();
    float height = image.height();
    Point x0y0(floor(ndcx*width), floor(ndcy*height), z);
    Point x1y0(ceil(ndcx*width), floor(ndcy*height), z);
    Point x0y1(floor(ndcx*width), ceil(ndcy*height), z);
    Point x1y1(ceil(ndcx*width), ceil(ndcy*height), z);
    float xWeight = ndcx*width - x0y0.x;
    float yWeight = ndcy*height - x0y0.x;
    Point value = lerp2d(x0y0, x1y0, x0y1, x1y1, xWeight, yWeight);
    return image(value.x*image.width(), value.y*image.height());
}

RGBColor ImageTexture::getColorDX(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor ImageTexture::getColorDY(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

}