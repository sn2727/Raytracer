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
    image.readPNG("../../"+filename);
    this -> bht = bh;
    this -> it = i;
}

ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i)
{
    this -> image = Image(image);
    this -> bht = bh;
    this -> it = i;
}

RGBColor ImageTexture::getColor(const Point& coord) {
    int width = image.width();
    int height = image.height();
    float ndcx = coord.x;
    float ndcy = coord.y;
    switch (bht)
    {
    case CLAMP:
        if (ndcx < 0) ndcx = 0; else if (ndcx > 1) ndcx = 1;
        if (ndcy < 0) ndcy = 0; else if (ndcy > 1) ndcy = 1;
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
        if (ndcx < 0) ndcx = ndcx - floor(ndcx);
        if (ndcx > 1) ndcx = ndcx - floor(ndcx);  
        if (ndcy < 0) ndcy = ndcy - floor(ndcy);
        if (ndcy > 1) ndcy = ndcy - floor(ndcy);

        if (it == NEAREST) return nearest(ndcx, ndcy);
        return bilinear(ndcx, ndcy, coord.z);
        break;
    default:
        return RGBColor::rep(0);
        break;
    }
}

RGBColor ImageTexture::nearest(float ndcx, float ndcy) {
    Point p(round(ndcx*image.width()), round(ndcy*image.height()), 0);
    p = format(p, image.width(), image.height());
    return image(p.x, p.y);
}

RGBColor ImageTexture::bilinear(float ndcx, float ndcy, float z) {
    int width = image.width();
    int height = image.height();
    Point x0y0(floor(ndcx*width), floor(ndcy*height), z);
    Point x1y0(ceil(ndcx*width), floor(ndcy*height), z);
    Point x0y1(floor(ndcx*width), ceil(ndcy*height), z);
    Point x1y1(ceil(ndcx*width), ceil(ndcy*height), z);
    x0y0 = format(x0y0, width, height);
    x1y0 = format(x1y0, width, height);
    x0y1 = format(x0y1, width, height);
    x1y1 = format(x1y1, width, height);
    float xWeight = ndcx*width - x0y0.x;
    float yWeight = ndcy*height - x0y0.y;
    RGBColor value = lerp2d(image(x0y0.x, x0y0.y), image(x1y0.x, x1y0.y), image(x0y1.x, x0y1.y), image(x1y1.x, x1y1.y), xWeight, yWeight);
    return value;
}

Point ImageTexture::format(Point p, int width, int height) {
    Point value = p;
    if (p.x >= width) value.x--;
    if (p.y >= height) value.y--;
    return value;
} 

RGBColor ImageTexture::getColorDX(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor ImageTexture::getColorDY(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

}